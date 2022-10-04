#include "channel.hpp"
#include "server.hpp"
#include <list>

#define iterator	std::map<std::string, Channel>::iterator

Channel*	findChannel(std::string &channelName, Server &server){
	iterator	it = server._channels.find(channelName);

	if (it != server._channels.end())
		return &(it->second);
	return NULL;
}

void 	removeUserFromChannel(Channel *channel, User &user, Server &server, std::string message){
	channel->removeUser(user, message);
	if (channel->isEmpty()){
		server._channels.erase(channel->getName());
	}
}
