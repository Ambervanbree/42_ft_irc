#include "channel.hpp"
#include "user.hpp"
#include "server.hpp"
#include "commands.hpp"

// NICK <nickname> <hopcount> <username> <host> <servertoken> <umode> <realname>
// -> Combination of NICK (the user version), USER and MODE.

/*Irssi send: 
- registration : USER <nick> <user> <host> :<realname>
- change nick : :<nick> USER <newnick>*/

void change_nickname(User &user, Server &server, const std::string &new_nickname)
{
	std::cerr << "initial nickname: " << user.getNickname() << std::endl;
	user.setNickname(new_nickname);
	(void)server;
	std::cerr << "Change nickname to " << user.getNickname() << std::endl;
}


void NICK(std::deque<std::string> command, User &user, Server &server)
{
	std::cerr << "Command NICK\n";
	if (command.size() == 3 && command[0].size() && command[0][0] == ':')
		change_nickname(user, server, command[2]);
	(void)command;
	(void)user;
	(void)server;
}