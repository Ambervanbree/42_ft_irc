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
