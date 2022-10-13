#include "channel.hpp"
#include "user.hpp"
#include "server.hpp"
#include "commands.hpp"

#define ARGUMENTS	 	server.getArgs()

void	channelList(User &user, Server &server){
	std::deque<std::string>	channels;
	char 					delimiter[] = ",";

	split_args(ARGUMENTS[0], delimiter, channels);	
	std::deque<std::string>::iterator	it = channels.begin();
	std::deque<std::string>::iterator	ite = channels.end();
	Channel		*chan;

	for (; it != ite; it++){
		chan = findChannel(*it, server);
		if (chan != NULL){
			// chan->getList(); will return the list
			// RPL sent to user:
			(void) user;
			std::cout << chan->getList() << std::endl;
			std::cout << "RPL_LIST (322)" << std::endl;
		}
	}
}

void	allListsUser(User &user, Server &server){
	std::map<std::string, Channel *>::iterator	it = server._channels.begin();
	std::map<std::string, Channel *>::iterator	ite = server._channels.end();

	for (; it != ite; it++){
		// it->second->getList(); will return the list
		// RPL sent to user:
		(void) user;
		std::cout << it->second->getList() << std::endl;
		std::cout << "RPL_LIST (322)" << std::endl;
	}
}

void LIST(User &user, Server &server){
	// if (!user.isRegistered())
	// 	return ;
	if (ARGUMENTS.empty())
		allListsUser(user, server);
	else
		channelList(user, server);
	// RPL sent to user:
	std::cout << "RPL_LISTEND (323)" << std::endl;
}

/*
	Note:
	According to the RFC there is no error reply for bad channel names.
*/