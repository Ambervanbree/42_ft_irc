#include "channel.hpp"
#include "user.hpp"
#include "server.hpp"
#include "commands.hpp"

#define TARGET command[1]
#define MODESTRING command[2]
#define MODEARG command[3]

// 	MODE <target> [<modestring> [<mode arguments>]]

void	addMode(char mode, std::string &modeArg, std::string nickMask, Channel *chan){
	switch (mode){
		case 'k':
			if (modeArg.empty())
				return ;
			else
				chan->setKey(modeArg, nickMask);
			modeArg.clear();
			return ;
		case 'b':
			if (modeArg.empty()){
				std::cout << "RPL_BANLIST (367)" << std::endl;
				return ;
			}
			chan->banUser(modeArg, nickMask);
			modeArg.clear();
			return ;
		default:
			std::cerr << "mode not handled (yet)" << std::endl;
			return ;
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
			std::cerr << "mode not handled (yet)" << std::endl;
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

void	channelMode(std::deque<std::string> &command, std::string nickMask, Server &server){
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

void MODE(std::deque<std::string> command, User &user, Server &server){
	if (TARGET[0] == '#')
		channelMode(command, user.getNickname(), server);
	else
		userMode();
}
