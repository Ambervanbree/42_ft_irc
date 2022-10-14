#include "channel.hpp"
#include "user.hpp"
#include "server.hpp"
#include "commands.hpp"

#define ARGUMENTS	 	server.getArgs()

void	channelNames(User &user, Server &server){
	std::vector<std::string>	channels;
	char 					delimiter[] = ",";

	split_args(ARGUMENTS[0], delimiter, channels);
	
	std::vector<std::string>::iterator	it = channels.begin();
	std::vector<std::string>::iterator	ite = channels.end();
	Channel		*chan;

	for (; it != ite; it++){
		chan = findChannel(*it, server);
		if (chan != NULL){
			// chan->getNames(); will return the names
			// RPL sent to user:
			(void) user;
			std::cout << chan->getNames() << std::endl;
			std::cout << "RPL_NAMREPLY (353)" << std::endl;
		}
	}
}

void	allNamesUser(User &user, Server &server){
	std::map<std::string, Channel *>::iterator	it = server._channels.begin();
	std::map<std::string, Channel *>::iterator	ite = server._channels.end();

	for (; it != ite; it++){
		// it->second->getNames(); will return the names
		// RPL sent to user:
		(void) user;
		std::cout << "RPL_NAMREPLY (353)" << std::endl;
		std::cout << it->second->getNames() << std::endl;
	}
}

void NAMES(User &user, Server &server){
	// if (!user.isRegistered())
	// 	return ;
	if (ARGUMENTS.empty())
		allNamesUser(user, server);
	else
		channelNames(user, server);
	// RPL sent to user:
	std::cout << "RPL_ENDOFNAMES (366)" << std::endl;
}

/*
	Note:
	According to the RFC there is no error reply for bad channel names.
*/