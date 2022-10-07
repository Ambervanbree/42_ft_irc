#include "channel.hpp"
#include "server.hpp"
#include <list>

Channel*	findChannel(std::string &channelName, Server &server){
	std::map<std::string, Channel>::iterator	it = server._channels.find(channelName);

	if (it != server._channels.end())
		return &(it->second);
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
		std::cout << "[+] Channel " << channel->getName() << " erased\n";
		server._channels.erase(channel->getName());
	}
}
