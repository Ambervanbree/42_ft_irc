#include "user.hpp"
#include "server.hpp"
#include<string>

// USER <username> <unused> <unused> :<realname>

void USER(User &user, Server &server)
{
	std::cout << "Command USER" << std::endl;
	if ((user.getPassChecked() == false) || (user.getNickname().compare("dflt nick") == 0))
		return;
	if (server._command.args.size() < 3 || server._command.trailer.empty()) {
		std::cerr << "(461) ERR_NEEDMOREPARAMS" << std::endl;
		return;
	}
	if (user.getRegistered()) {
		std::cerr << "ERR_ALREADYREGISTERED (462)" << std::endl;
		return;
	}
	
	std::string username = server._command.args[0];
	server._command.trailer.erase(0, 1);
    std::string realname = server._command.trailer;

	while (username.length() > USERLEN)
		username.erase(username.end()--);
	user._setUsername(username);
	user._setRealname(realname);
	user.setRegistered();
	std::cerr << "(001) RPL_WELCOME" << std::endl;
	return;
}
