#include "user.hpp"
#include "server.hpp"

// USER <username> <mode> <unused> <realname>

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
	user._setUsername(username);
	user._setRealname(realname);
	return;
}
