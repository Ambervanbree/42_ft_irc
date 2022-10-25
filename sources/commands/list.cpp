#include "channel.hpp"
#include "user.hpp"
#include "server.hpp"
#include "commands.hpp"

#define ARGUMENTS	 	server.getArgs()

void	channelList(User &user, Server &server){
	std::vector<std::string>	channels;
	char 						delimiter[] = ",";

	split_args(ARGUMENTS[0], delimiter, channels);	
	std::vector<std::string>::iterator	it = channels.begin();
	std::vector<std::string>::iterator	ite = channels.end();
	Channel		*chan;

	for (; it != ite; it++){
		chan = findChannel(*it, server);
		if (chan != NULL){
			user.addRepliesToBuffer(RPL_LIST(user.getNickname(), chan->getName(), toString(chan->size()), chan->getTopic()));
			user.addRepliesToBuffer(RPL_LISTEND(user.getNickname()));
		}
	}
}

void	allListsUser(User &user, Server &server){
	std::map<std::string, Channel *>::iterator	it = server._channels.begin();
	std::map<std::string, Channel *>::iterator	ite = server._channels.end();

	for (; it != ite; it++){
		user.addRepliesToBuffer(RPL_LIST(user.getNickname(), it->second->getName(), toString(it->second->size()), it->second->getTopic()));
		user.addRepliesToBuffer(RPL_LISTEND(user.getNickname()));
	}
}

void LIST(User &user, Server &server){
	if (!user.isRegistered())
		return ;
	if (ARGUMENTS.empty())
		allListsUser(user, server);
	else
		channelList(user, server);
}

/*
	Note:
	According to the RFC there is no error reply for bad channel names.
*/