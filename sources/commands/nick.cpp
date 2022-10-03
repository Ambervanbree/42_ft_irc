#include "channel.hpp"
#include "user.hpp"
#include "server.hpp"
#include "commands.hpp"

// NICK <nickname> <hopcount> <username> <host> <servertoken> <umode> <realname>
// -> Combination of NICK (the user version), USER and MODE.

/*Irssi send: 
- registration : USER <nick> <user> <host> :<realname>
- change nick : :<nick> USER <newnick>*/

void NICK(Command command, User &user, Server &server)
{
	std::cout << "Command NICK" << std::endl;
	std::cout << "initial nickname: " << user.getNickname() << std::endl;
	user._setNickname(command.args[0]);
	std::cout << "Changed nickname to " << user.getNickname() << std::endl;
}