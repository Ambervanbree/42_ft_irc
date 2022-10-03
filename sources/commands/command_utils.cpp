#include "channel.hpp"
#include "server.hpp"
#include <list>

Channel*	findChannel(std::string &channelName, Server &server){
	std::list<Channel>::iterator	it = server._channels.begin();
	std::list<Channel>::iterator	ite = server._channels.end();

	for (; it != ite; it++){
		if (it->getName() == channelName)
			return &(*it);
	}
	return NULL;
}

void 	removeUserFromChannel(Channel *channel, User &user, Server &server, std::string message){
	channel->removeUser(user, message);
	if (channel->isEmpty()){
		std::list<Channel>::iterator	it = server._channels.begin();
		std::list<Channel>::iterator	ite = server._channels.end();

		for (; it != ite; it++){
			if (it->getName() == channel->getName()){
				std::cout << "Channel " << channel->getName() << " deleted" << std::endl;
				server._channels.erase(it);
				break ;
			}
		}
	}
}
