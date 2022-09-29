#include "channel.hpp"
#include "server.hpp"
#include <list>

Channel*	findChannel(std::string &channelName, Server &server){
	std::set<Channel *>::iterator	it = server._channels.begin();
	std::set<Channel *>::iterator	ite = server._channels.end();

	for (; it != ite; it++){
		if ((*it)->getName() == channelName)
			return *it;
	}
	return NULL;
}
