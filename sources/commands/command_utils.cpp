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
			std::string message = "PART " + chan->second->getName() + "\r\n";
			chan->second->sendChannelMessage(user, server, message);
		}
	}
}

std::string	createCommandMessage(Server &server){
	std::string message = " " + server.getCommand() + " ";
	for (size_t i = 0; i < server.getArgs().size(); i++)
		message += server.getArgs()[i] + " ";
	if (!server.getTrailer().empty())
		message += "\"" + server.getTrailer() + "\"\r\n";
	return message ;
}

bool    isOperator(const std::string &username, Server &server) {
    std::list<std::string>::iterator it = server.operators.begin();
    std::list<std::string>::iterator ite = server.operators.end();

    for (;it != ite; it++) {
        if (username.compare(*it) == 0)
            return 1;
    }
    return 0;
}