#include "channel.hpp"
#include "user.hpp"
#include "server.hpp"
#include "commands.hpp"

#define TARGET command[1]
#define MODESTRING command[2]
#define MODEARG command[3]

// MODE <target> [<modestring> [<mode arguments>]]

void	parseModeString(std::string modestring, std::deque<char> plus, std::deque<char> min){
	std::string::iterator	it 	= modestring.begin();
	std::string::iterator	ite = modestring.end();

	if (!(*it == '+' || *it == '-'))
		return ;

	for (; it != ite; ){
		switch (*(it++)){
			case '+':
				while (!(*it == '+' || *it == '-' || it == ite)){
					plus.push_back(*it);
					std::cout << "pushed " << *it << " to plus" << std::endl;
					it++;
				}
			case '-':
				while (!(*it == '+' || *it == '-' || it == ite)){
					min.push_back(*it);
					std::cout << "pushed " << *it << " to min" << std::endl;
					it++;
				}
		}
		if (it == ite)
			return ;
	}
}

void	channelMode(std::deque<std::string> &command, User &user, Server &server){
	Channel		*chan = findChannel(TARGET, server);

	if (chan == NULL){
		std::cerr << "ERR_NOSUCHCHANNEL (403)" << std::endl;
		// ERR: "<client> <channel> :No such channel"
		return ;	
	}
	if (MODESTRING.empty()){
		std::cout << "List channel modes" << std::endl;
		// TODO --> reply RPL_CHANNELMODEIS (324)
		return ;
	}

	std::deque<char>	plus;
	std::deque<char>	min;

	parseModeString(MODESTRING, plus, min);
	(void)user;
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
