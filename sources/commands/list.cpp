#include "channel.hpp"
#include "user.hpp"
#include "server.hpp"
#include "commands.hpp"

// LIST [ <channel> ]

#define CHANNELS	 	server.getArgs()[0]

void	channelList(User &user, Server &server){
	std::deque<std::string>	channels;
	char 					delimiter[] = ",";

	split_args(CHANNELS, delimiter, channels);	
	std::deque<std::string>::iterator	it = channels.begin();
	std::deque<std::string>::iterator	ite = channels.end();
	Channel		*temp;

	for (; it != ite; it++){
		temp = findChannel(*it, server);
		if (temp != NULL)
			temp->sendList(user);
	}	
}

void	allListsUser(User &user, Server &server){
	std::map<std::string, Channel>::iterator	it = server._channels.begin();
	std::map<std::string, Channel>::iterator	ite = server._channels.end();

	for (; it != ite; it++){
		if (it->second.onChannel(user))
			it->second.sendList(user);
	}
}

void LIST(User &user, Server &server){
	if (CHANNELS.empty())
		allListsUser(user, server);
	else
		channelList(user, server);
}