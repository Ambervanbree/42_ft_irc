// #include "channel.hpp"
#include "user.hpp"
#include "server.hpp"
// #include "commands.hpp"

// NICK <nickname> <hopcount> <username> <host> <servertoken> <umode> <realname>
// -> Combination of NICK (the user version), USER and MODE.

/*Irssi send: 
- registration : USER <nick> <user> <host> :<realname>
- change nick : :<nick> USER <newnick>*/

void NICK(User &user, Server &server)
{
	std::cout << "Command NICK" << std::endl;
	std::cout << "Nickname before command NICK: " << user.getNickname() << std::endl;
	if (server._command.args.size() && (server._command.args[0] != "\0"))
		user._setNickname(server._command.args[0]);
	else
		std::cerr << "(431) ERR_NONICKNAMEGIVEN" << std::endl;
	(void)server;
	std::cout << "Nickname after command NICK: " << user.getNickname() << std::endl;
}