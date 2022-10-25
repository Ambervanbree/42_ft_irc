#include "channel.hpp"
#include "user.hpp"
#include "server.hpp"
#include "commands.hpp"

#define ARGUMENTS	 	server.getArgs()

void	channelNames(User &user, Server &server){
	std::vector<std::string>	channels;
	char 						delimiter[] = ",";

	split_args(ARGUMENTS[0], delimiter, channels);
	
	std::vector<std::string>::iterator	it = channels.begin();
	std::vector<std::string>::iterator	ite = channels.end();
	Channel		*chan;

	for (; it != ite; it++){
		chan = findChannel(*it, server);
		if (chan != NULL)
			chan->sendNames(user);
	}
}

void	allNamesUser(User &user, Server &server){
	std::map<std::string, Channel *>::iterator	it = server._channels.begin();
	std::map<std::string, Channel *>::iterator	ite = server._channels.end();

	for (; it != ite; it++)
		it->second->sendNames(user);
}

void NAMES(User &user, Server &server){
	if (!user.isRegistered())
		return ;
	if (ARGUMENTS.empty())
		allNamesUser(user, server);
	else
		channelNames(user, server);
}

/*
	Note:
	According to the RFC there is no error reply for bad channel names.
*/