#include "user.hpp"
#include "server.hpp"

// USER <username> <mode> <unused> <realname>

int	wrongGrammar(const std::string &nick) {
	char forbidden[] = {' ', ',', '*', '?', '!', '@', '.'};
	char wrongStart[] = {'&', ':', '#'};
	unsigned long i = 0;

	if (nick.length() > 9)
		return 1;
	if ((nick[0] == wrongStart[0]) || nick[0] == wrongStart[1]
		|| nick[0] == wrongStart[2])
		return 1;
	for(; i < sizeof(forbidden); i++) {
		if (nick.find(forbidden[i]) != std::string::npos)
			return 1;
	}
	return 0;
}

int	existingNick(const std::string &nick, Server &server) {
	std::list<User>::iterator	ite;

	for(ite = server.users.begin(); ite != server.users.end(); ite++){
		if ((*ite).getNickname().compare(nick) == 0)
			return 1;
	}
	return 0;
}

void USER(User &user, Server &server)
{
	std::cout << "Command USER" << std::endl;
	if (server._command.args.size() < 3 || server._command.trailer.empty()) {
		std::cerr << "(461) ERR_NEEDMOREPARAMS" << std::endl;
		return;
	}
	std::string username = server._command.args[0];
	// NOTE: args[1] and args[2] must be present but are not taken
	// into consideration (depends on the IRC version and we can 
	// decide it has no meaning... :D)
    std::string realname = server._command.trailer;

	while (username.length() > USERLEN)
		username.pop_back();
	// -----> TO DO : create or use the alreadyRegistered function
	// if (alreadyRegistered) {}
	// 	std::cerr << "ERR_ALREADYREGISTERED (462)" << std::endl;
	// 	return;
	// }
	user._setNickname(nick);
	return;
}
