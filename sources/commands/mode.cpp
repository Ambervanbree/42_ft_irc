#include "channel.hpp"
#include "user.hpp"
#include "server.hpp"
#include "commands.hpp"

#define TARGET	 	server.getArgs()[0]
#define MODESTRING 	server.getArgs()[1]
#define MODEARG		server.getArgs()[2]
// 	MODE <target> [<modestring> [<mode arguments>]]

void	addMode(char mode, std::string &modeArg, std::string nickMask, Channel *chan){
	switch (mode){
		case 'k':
			if (modeArg.empty())
				return ;
			else
				chan->setKey(modeArg, nickMask);
			return ;
		case 'b':
			if (modeArg.empty()){
				std::cout << "RPL_BANLIST (367)" << std::endl;
				std::cout << "RPL_ENDOFBANLIST (368)" << std::endl;
				return ;
			}
			chan->banUser(modeArg, nickMask);
			return ;
		default:
			std::cerr << "mode not handled (yet)" << std::endl;
			return ;
		// TODO ----> clear modeARG
		// TODO ----> check number of arguments for every function
	}
}

void	eraseMode(char mode, std::string &modeArg, std::string nickMask, Channel *chan){
	switch (mode){
		case 'k':
			chan->unsetKey(nickMask);
			return ;
		case 'b':
			if (modeArg.empty()){
				std::cout << "ERR_NEEDMOREPARAMS (461)" << std::endl;
				return ;
			}
			chan->unbanUser(modeArg, nickMask);
			modeArg.clear();
			return ;
		default:
			std::cerr << "ERR_UMODEUNKNOWNFLAG (501)" << std::endl;
			// ++ MODE message
			return ;
	}	
}

void	parseModeString(std::string &modeString, std::string &modeArg, std::string nickMask, Channel *chan){
	std::string::iterator	it 	= modeString.begin();
	std::string::iterator	ite = modeString.end();

	if (!(*it == '+' || *it == '-'))
		return ;

	for (; it != ite; ){
		switch (*(it++)){
			case '+':
				while (!(*it == '+' || *it == '-' || it == ite)){
					addMode(*it, modeArg, nickMask, chan);
					it++;
				}
			case '-':
				while (!(*it == '+' || *it == '-' || it == ite)){
					eraseMode(*it, modeArg, nickMask, chan);
					it++;
				}
		}
		if (it == ite)
			return ;
	}
}

void	channelMode(std::string nickMask, Server &server){
	Channel		*chan = findChannel(TARGET, server);

	if (chan == NULL){
		std::cerr << "ERR_NOSUCHCHANNEL (403)" << std::endl;
		return ;	
	}
	if (MODESTRING.empty()){
		std::cout << "RPL_CHANNELMODEIS (324)" << std::endl;
		return ;
	}
	parseModeString(MODESTRING, MODEARG, nickMask, chan);
}

void	userMode(){
	// TODO --> function to change user mode
	std::cout << "User MODE requested" << std::endl;
}

void MODE(User &user, Server &server){
	if (TARGET[0] == '#')
		channelMode(user.getNickname(), server);
	else
		userMode();
}
