#include "channel.hpp"
#include "user.hpp"
#include "server.hpp"
#include "commands.hpp"

#define TARGET command[1]
#define MODESTRING command[2]
#define MODEARG command[3]

// MODE <target> [<modestring> [<mode arguments>]]

void	channelMode(std::deque<std::string> &command, User &user, Server &server){
	Channel		*chan = findChannel(TARGET, server);

	if (chan == NULL){
		std::cerr << "ERR_NOSUCHCHANNEL (403)" << std::endl;
		// ERR: "<client> <channel> :No such channel"
		return ;	
	}
	if (MODESTRING.empty()){
		// TODO --> reply RPL_CHANNELMODEIS (324)
		return ;
	}
	
	// TODO --> check if user has priviliges to change channel mode
	// ERR_CHANOPRIVSNEEDED (482)

	switch (MODESTRING[0]){
		case '+':
			chan->setMode(MODESTRING, MODEARG);
		case '-':
			chan->unsetMode(MODESTRING, MODEARG);
		default:
			return ;
	}
}

void	userMode(std::deque<std::string> &command, User &user, Server &server){
	// TODO --> function to change user mode
}


void 	MODE(std::deque<std::string> &command, User &user, Server &server)
{
	std::deque<std::string> 
	
	if (TARGET[0] = '#')
		channelMode(command, user, server);
	else
		userMode(command, user, server);
}