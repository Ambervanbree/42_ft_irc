#include "user.hpp"
#include "server.hpp"
#include <string>

// USER <username> <unused> <unused> :<realname>

void USER(User &user, Server &server)
{
	std::string toSend;
	if ((user.isPassChecked() == false) || (user.getNickname().compare("dflt_nick") == 0))
		return;
	if (server._command.args.size() < 3 || server._command.trailer.empty()) {
		toSend = ERR_NEEDMOREPARAMS(user.getNickname(), server.getCommand());
		std::cerr << toSend << std::endl;
		server.addReplies(user, toSend);
		return;
	}
	if (user.isRegistered()) {
		toSend = ERR_ALREADYTREGISTERED(user.getNickname());
		std::cerr << toSend << std::endl;
		server.addReplies(user, toSend);
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
	toSend = RPL_WELCOME(user.getNickname());
	std::cerr << toSend << std::endl; 
	server.addReplies(user, toSend);
	return;
}
