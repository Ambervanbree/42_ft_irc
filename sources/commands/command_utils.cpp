#include "channel.hpp"
#include "server.hpp"
#include <list>

#define iterator	std::map<std::string, Channel>::iterator

Channel*	findChannel(std::string &channelName, Server &server){
	iterator	it = server._channels.find(channelName);

	if (it != server._channels.end())
		return &(it->second);
	return NULL;
	// std::list<Channel>::iterator	ite = server._channels.end();

	// for (; it != ite; it++){
	// 	if (it->getName() == channelName)
	// 		return &(*it);
	// }
	// return NULL;
}

void 	removeUserFromChannel(Channel *channel, User &user, Server &server, std::string message){
	channel->removeUser(user, message);
	if (channel->isEmpty()){
		server._channels.erase(channel->getName());
		// std::list<Channel>::iterator	it = server._channels.begin();
		// std::list<Channel>::iterator	ite = server._channels.end();

		// for (; it != ite; it++){
		// 	if (it->getName() == channel->getName()){
		// 		std::cout << "Channel " << channel->getName() << " deleted" << std::endl;
		// 		server._channels.erase(it);
		// 		break ;
		// 	}
		// }
	}
}
