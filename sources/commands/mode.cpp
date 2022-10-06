#include "channel.hpp"
#include "user.hpp"
#include "server.hpp"
#include "commands.hpp"

#define TARGET	 	server.getArgs()[0]
#define MODESTRING 	server.getArgs()[1]

// 	MODE <target> [<modestring> [<mode arguments>]]

struct Mode{
	Channel					*chan;
	std::string				nickMask;
	std::string				modeString;
	std::deque<std::string>	modeArg;
	int						argNr;
};

void	addMode(char toSet, Mode &mode){
	switch (toSet){
		case 'k':
			if (mode.modeArg.empty()){
				std::cout << "ERR_NEEDMOREPARAMS (461)" << std::endl;
				return ;
			}
			else if (mode.argNr < 3){
				mode.chan->setKey(mode.modeArg[mode.argNr], mode.nickMask);
				mode.argNr++;
			}
			return ;
		case 'b':
			if (mode.modeArg.empty()){
				std::cout << "RPL_BANLIST (367)" << std::endl;
				std::cout << "RPL_ENDOFBANLIST (368)" << std::endl;
				return ;
			}
			if (mode.argNr < 3){
				mode.chan->banUser(mode.modeArg[mode.argNr], mode.nickMask);
				mode.argNr++;
			}
			return ;
		default:
			std::cerr << "ERR_UNKNOWNMODE (472)" << std::endl;
			std::cout << "RPL_CHANNELMODEIS (324)" << std::endl;
			return ;
	}
}

void	eraseMode(char toSet, Mode &mode){
	switch (toSet){
		case 'k':
			mode.chan->unsetKey(mode.nickMask);
			return ;
		case 'b':
			if (mode.modeArg.empty()){
				std::cout << "ERR_NEEDMOREPARAMS (461)" << std::endl;
				return ;
			}
			if (mode.argNr < 3){
				mode.chan->unbanUser(mode.modeArg[mode.argNr], mode.nickMask);
				mode.argNr++;
			}
			return ;
		default:
			std::cerr << "ERR_UNKNOWNMODE (472)" << std::endl;
			std::cout << "RPL_CHANNELMODEIS (324)" << std::endl;
			return ;
	}	
}

void	parseModeString(Mode &mode){
	std::string::iterator	it 	= mode.modeString.begin();
	std::string::iterator	ite = mode.modeString.end();

	if (!(*it == '+' || *it == '-'))
		return ;

	for (; it != ite; ){
		switch (*(it++)){
			case '+':
				while (!(*it == '+' || *it == '-' || it == ite)){
					addMode(*it, mode);
					it++;
				}
			case '-':
				while (!(*it == '+' || *it == '-' || it == ite)){
					eraseMode(*it, mode);
					it++;
				}
		}
		if (it == ite)
			return ;
	}
}

void	fillModeStruct(Mode &mode, std::string nickMask, Channel *channel, Server &server){
	mode.chan			= channel;
	mode.modeString 	= MODESTRING;
	mode.nickMask 		= nickMask;
	mode.argNr			= 0;
	size_t args 		= server.getArgs().size() - 2;
	std::string			temp;

	for (size_t i = 0; i < args; i++){
		temp = server.getArgs()[i+2];
		if (temp[0] == '+' || temp[0] == '-')
			mode.modeString.append(temp);
		else
			mode.modeArg.push_back(temp);
	}
}

void	channelMode(std::string nickMask, Server &server){
	Channel		*chan = findChannel(TARGET, server);

	if (chan == NULL){
		std::cerr << "ERR_NOSUCHCHANNEL (403)" << std::endl;
		return ;	
	}
	if (server.getArgs().size() < 2){
		std::cout << "RPL_CHANNELMODEIS (324)" << std::endl;
		return ;
	}

	Mode	mode;

	fillModeStruct(mode, nickMask, chan, server);
	parseModeString(mode);
}

void	userMode(){
	std::cerr << "ERR_UMODEUNKNOWNFLAG (501)" << std::endl;
	std::cerr << "RPL_UMODEIS (221)" << std::endl;
	return ;
}

void MODE(User &user, Server &server){
	if (!user.getRegistered())
		return ;
	if (server.getArgs().empty()){
		std::cout << "ERR_NEEDMOREPARAMS (461)" << std::endl;
		return ;		
	}
	if (TARGET[0] == '#')
		channelMode(user.getNickMask(), server);
	else
		userMode();
}
