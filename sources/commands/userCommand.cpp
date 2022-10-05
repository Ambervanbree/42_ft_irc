#include "user.hpp"
#include "server.hpp"
#include<string>

// USER <username> <unused> <unused> :<realname>

void USER(User &user, Server &server)
{
	std::cout << "Command USER" << std::endl;
	if ((user._isPassChecked == false) || (user.getNickname().compare("dflt nick") == 0))
		return;
	if (server._command.args.size() < 3 || server._command.trailer.empty()) {
		std::cerr << "(461) ERR_NEEDMOREPARAMS" << std::endl;
		return;
	}
	// -----> TO DO : use the _isRegistered bool
	if (user._isRegistered) {
		std::cerr << "ERR_ALREADYREGISTERED (462)" << std::endl;
		return;
	}
	
	std::string username = server._command.args[0];
	// NOTE: args[1] and args[2] must be present but are not taken
	// into consideration (depends on the IRC version and we can 
	// decide it has no meaning... :D)
	server._command.trailer.erase(0, 1);
    std::string realname = server._command.trailer;

	// -------> TO DO : depending on parsing, to be taken intoaccount:
	//  The minimum length of <username> is 1, ie. it MUST not be empty.

	while (username.length() > USERLEN)
		username.erase(username.end()--);
	user._setUsername(username);
	user._setRealname(realname);
	user._isRegistered = true;
	return;
}
