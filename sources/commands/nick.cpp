#include "user.hpp"
#include "server.hpp"

// NICK <nickname> <hopcount> <username> <host> <servertoken> <umode> <realname>
// -> Combination of NICK (the user version), USER and MODE.

/*Irssi send: 
- registration : USER <nick> <user> <host> :<realname>
- change nick : :<nick> USER <newnick>*/

int	wrongGrammar(const std::string &nick) {
	if (nick.length() > 9)
		return 1;
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
	std::cout << "Nickname before command NICK: " << user.getNickname() << std::endl;
	if (server._command.args.size() == 0 || (server._command.args[0] == "\0"))
		std::cerr << "(431) ERR_NONICKNAMEGIVEN" << std::endl;

	std::string nick = server._command.args[0];

	if (wrongGrammar(nick))
		std::cerr << "(432) ERR_ERRONEUSNICKNAME" << std::endl;
	else if (existingNick(nick, server))
		std::cerr << "(433) ERR_NICKNAMEINUSE" << std::endl;
	else
		user._setNickname(nick);
	std::cout << "Nickname after command NICK: " << user.getNickname() << std::endl;
}
