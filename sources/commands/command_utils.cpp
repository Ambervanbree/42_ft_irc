#include "channel.hpp"
#include "server.hpp"
#include <list>

Channel*	findChannel(std::string &channelName, Server &server){
	std::map<std::string, Channel *>::iterator	it = server._channels.find(channelName);

	if (it != server._channels.end())
		return (it->second);
	return NULL ;
}

User*		findUser(std::string &userName, Server &server){
	std::list<User>::iterator	it	= server.users.begin();
	std::list<User>::iterator	ite	= server.users.end();

	for (; it != ite; it++){
		if (it->getNickname() == userName)
			return &(*it);
	}
	return NULL ;
}

void 		removeUserFromChannel(Channel *channel, User &user, Server &server){
	
	channel->removeUser(user);
	if (channel->isEmpty()){
		delete channel;
		server._channels.erase(channel->getName());
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
			removeUserFromChannel(chan->second, user, server);
			chan->second->sendChannelMessage(user, PART_message(chan->second->getName()));
		}
	}
}

void		channelWelcomeMessage(Channel &chan, User &user){
	chan.sendChannelMessage(user, JOIN_message(chan.getName()));
	chan.sendTopic(user);
	user.addRepliesToBuffer(RPL_NAMREPLY(user.getNickname(), chan.getName(), chan.getNames()));
}