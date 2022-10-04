#include "channel.hpp"
#include "user.hpp"
#include "server.hpp"
#include "commands.hpp"

// NAMES [ <channel> ]

#define CHANNELS	 	server.getArgs()[0]

void	channelNames(User &user, Server &server){
	std::deque<std::string>	channels;
	char 					delimiter[] = ",";

	split_args(CHANNELS, delimiter, channels);
	
	std::deque<std::string>::iterator	it = channels.begin();
	std::deque<std::string>::iterator	ite = channels.end();
	Channel		*temp;

	for (; it != ite; it++){
		temp = findChannel(*it, server);
		if (temp != NULL)
			temp->sendNames(user);
	}
}

void	allNamesUser(User &user, Server &server){
	std::map<std::string, Channel>::iterator	it = server._channels.begin();
	std::map<std::string, Channel>::iterator	ite = server._channels.end();

	for (; it != ite; it++){
		if (it->second.onChannel(user))
			it->second.sendNames(user);
	}
}

void NAMES(User &user, Server &server){
	if (CHANNELS.empty())
		allNamesUser(user, server);
	else
		channelNames(user, server);
}
