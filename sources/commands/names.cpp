#include "channel.hpp"
#include "user.hpp"
#include "server.hpp"
#include "commands.hpp"

#define CHANNELS	 	server.getArgs()[0]

void	channelNames(Server &server){
	std::deque<std::string>	channels;
	char 					delimiter[] = ",";

	split_args(CHANNELS, delimiter, channels);
	
	std::deque<std::string>::iterator	it = channels.begin();
	std::deque<std::string>::iterator	ite = channels.end();
	Channel		*temp;

	for (; it != ite; it++){
		temp = findChannel(*it, server);
		if (temp != NULL){
			//replies for channel:
			std::cout << "RPL_NAMREPLY" << std::endl;
			std::cout << "RPL_ENDOFNAMES" << std::endl;
		}
	}
}

void	userNames(User &user, Server &server){
	std::map<std::string, Channel>::iterator	it = server._channels.begin();
	std::map<std::string, Channel>::iterator	ite = server._channels.end();

	for (; it != ite; it++){
		if (it->second.onChannel(user)){
			//replies for channel:
			std::cout << "RPL_NAMREPLY" << std::endl;
			std::cout << "RPL_ENDOFNAMES" << std::endl;		
		}
	}
}

void NAMES(User &user, Server &server){
	if (CHANNELS.empty())
		userNames(user, server);
	else
		channelNames(server);
}
