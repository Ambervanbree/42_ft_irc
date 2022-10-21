#include "channel.hpp"
#include "server.hpp"
#include <list>

Channel*	findChannel(std::string &channelName, Server &server){
	std::map<std::string, Channel *>::iterator	it = server._channels.find(channelName);

	if (it != server._channels.end())
		return (it->second);
	return NULL ;
}

User*		findUser(std::string &nickName, Server &server){
	std::list<User>::iterator	it	= server.users.begin();
	std::list<User>::iterator	ite	= server.users.end();

	for (; it != ite; it++){
		if (it->getNickname() == nickName)
			return &(*it);
	}
	return NULL ;
}

void 		removeUserFromChannel(Channel *channel, User &user, Server &server){
	
	channel->removeUser(user);
	if (channel->isEmpty()){
		server._channels.erase(channel->getName());
		delete channel;
	}
}

void 		partFromAllChannels(User &user, Server &server){
	std::map<std::string, Channel *>::iterator	it 	= server._channels.begin();
	std::map<std::string, Channel *>::iterator	ite = server._channels.end();
	std::map<std::string, Channel *>::iterator 	chan;

	while (it != ite){
		chan = it;
		it++;
		if (chan->second->onChannel(user)){
			chan->second->sendChannelMessage(user, PART_message(chan->second->getName()));
			removeUserFromChannel(chan->second, user, server);
		}
	}
}

void		channelWelcomeMessage(Channel &chan, User &user){
	chan.sendChannelMessage(user, JOIN_message(chan.getName()));
	chan.sendTopic(user);
	user.addRepliesToBuffer(RPL_NAMREPLY(chan.getName(), chan.getNames()));
}

bool  	  isOperator(const std::string &username, Server &server) {
    std::list<std::string>::iterator it = server.operators.begin();
    std::list<std::string>::iterator ite = server.operators.end();

    for (;it != ite; it++) {
        if (username.compare(*it) == 0)
            return 1;
    }
    return 0;
}
