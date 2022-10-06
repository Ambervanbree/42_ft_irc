#include "channel.hpp"
#include "user.hpp"
#include "server.hpp"
#include "commands.hpp"

//KICK <channel> <user> [<comment>]

#define CHANNELS 	server.getArgs()[0]
#define USERS	 	server.getArgs()[1]
#define COMMENT 	server._command.trailer

void KICK(User &user, Server &server){
	if (!user.getRegistered())
		return ;
	if (server.getArgs().size() < 2){
		std::cerr << "ERR_NEEDMOREPARAMS (461)" << std::endl;
		return ;
	}
	std::deque<std::string>	channels;
	std::deque<std::string>	users;
	char 					delimiter[] = ",";

	split_args(CHANNELS, delimiter, channels);
	split_args(USERS, delimiter, users);

	





	if (!COMMENT.empty()){
		// message sent to channel
		std::cout << "[+] KICK message: user " << " nick " 
			<< " removed from channel " << " #chan " << " by " << " user " << std::endl;
	}
	else{
	// message sent to channel
		std::cout << "[+] KICK message: user " << " nick " 
			<< " removed from channel " << " #chan " << " with reason \""
			<< COMMENT << "\"" << std::endl;
	}
}