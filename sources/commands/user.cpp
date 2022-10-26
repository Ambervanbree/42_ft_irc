#include "user.hpp"
#include "server.hpp"
#include <string>

// USER <username> <unused> <unused> :<realname>

void USER(User &user, Server &server)
{
	if ((user.isPassChecked() == false) || (user.getNickname().compare("dflt_nick") == 0))
		return;
	if (server._command.args.size() < 3 || server._command.trailer.empty()) {
		user.addRepliesToBuffer(ERR_NEEDMOREPARAMS(user.getNickname(), server.getCommand()));
		return;
	}
	if (user.isRegistered()) {
		user.addRepliesToBuffer(ERR_ALREADYTREGISTERED(user.getNickname()));
		return;
	}
	
	std::string username = server._command.args[0];
    std::string realname = server._command.trailer;

	if (username.size() > USERLEN)
		user.setUsername(username.erase(USERLEN, username.size()));
	else
		user.setUsername(username);
	user.setRealname(realname.erase(0, 1));
	user.setRegistered();
	user.addRepliesToBuffer(RPL_WELCOME(user.getNickname(), user.getNickMask()));
	user.addRepliesToBuffer(RPL_YOURHOST(user.getNickname()));
	user.addRepliesToBuffer(RPL_CREATED(user.getNickname(), server.getTimeInfo()));
	user.addRepliesToBuffer(RPL_MYINFO(user.getNickname()));
	return;
}
