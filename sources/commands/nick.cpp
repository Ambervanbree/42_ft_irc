#include "user.hpp"
#include "server.hpp"

// NICK <nickname>

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

void NICK(User &user, Server &server)
{
	std::cout << "Command NICK" << std::endl;
	if (user.getPassChecked() == false)
		return;
	if (server._command.args.empty()) {
		std::cerr << "(431) ERR_NONICKNAMEGIVEN" << std::endl;
		return;
	}
	std::string nick = server._command.args[0];
	if (wrongGrammar(nick))
		std::cerr << "(432) ERR_ERRONEUSNICKNAME" << std::endl;
	else if (existingNick(nick, server))
		std::cerr << "(433) ERR_NICKNAMEINUSE" << std::endl;
	else
		user._setNickname(nick);
	return;
}
