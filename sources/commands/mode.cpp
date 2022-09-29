#include "channel.hpp"
#include "user.hpp"
#include "server.hpp"
#include "commands.hpp"

#define TARGET command[1]
#define MODESTRING command[2]
#define MODEARG command[3]

// MODE <target> [<modestring> [<mode arguments>]]

void	addMode(char mode, std::string &modeArg, User &user, Channel *chan){
	switch (mode){
		case 'k':
			if (modeArg.empty())
				return ;
			else
				chan->setKey(modeArg, user);
			modeArg.clear();
			return ;
		case 'b':
			if (modeArg.empty()){
				std::cout << "RPL_BANLIST (367)" << std::endl;
				return ;
			}
			chan->banUser(modeArg, user);
			modeArg.clear();
			return ;
		default:
			std::cerr << "mode not handled (yet)" << std::endl;
			return ;
	}
}

void	eraseMode(char mode, std::string &modeArg, User &user, Channel *chan){
	switch (mode){
		case 'k':
			chan->unsetKey(user);
			return ;
		case 'b':
			if (modeArg.empty()){
				std::cout << "ERR_NEEDMOREPARAMS (461)" << std::endl;
				return ;
			}
			chan->unbanUser(modeArg, user);
			modeArg.clear();
			return ;
		default:
			std::cerr << "mode not handled (yet)" << std::endl;
			return ;
	}	
}

void	parseModeString(std::string &modeString, std::string &modeArg, User &user, Channel *chan){
	std::string::iterator	it 	= modeString.begin();
	std::string::iterator	ite = modeString.end();

	if (!(*it == '+' || *it == '-'))
		return ;

	for (; it != ite; ){
		switch (*(it++)){
			case '+':
				while (!(*it == '+' || *it == '-' || it == ite)){
					if (!modeArg.empty())
						modeString.erase(it + 1, ite);
					addMode(*it, modeArg, user, chan);
					it++;
				}
			case '-':
				while (!(*it == '+' || *it == '-' || it == ite)){
					if (!modeArg.empty())
						modeString.erase(it + 1, ite);
					// eraseMode(*it, modeArg);
					it++;
				}
		}
		if (it == ite)
			return ;
	}
}

// bool 	connectModeArg(std::string &modeString, std::string &modeArg, char &arg){
// 	std::string::iterator	it = modeString.begin();
// 	std::string::iterator	ite = modeString.end();

// 	for (; it != ite; it++){
// 		switch (*it){
// 			case 'k':
// 				modeString.erase(++it, ite);
// 				arg = *it;
// 			case 't':
// 				modeString.erase(++it, ite);
// 				arg = *it;				
// 		}
// 	}
// }

void	channelMode(std::deque<std::string> &command, User &user, Server &server){
	Channel		*chan = findChannel(TARGET, server);

	if (chan == NULL){
		std::cerr << "ERR_NOSUCHCHANNEL (403)" << std::endl;
		return ;	
	}
	if (MODESTRING.empty()){
		std::cout << "RPL_CHANNELMODEIS (324)" << std::endl;
		return ;
	}
	parseModeString(MODESTRING, MODEARG, user, chan);
}

void	userMode(){
	// TODO --> function to change user mode
	std::cout << "User MODE requested" << std::endl;
}

void MODE(std::deque<std::string> command, User &user, Server &server){
	if (TARGET[0] == '#')
		channelMode(command, user, server);
	else
		userMode();
}
