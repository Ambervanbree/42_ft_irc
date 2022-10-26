#include "user.hpp"
#include "server.hpp"

// PASS <password> <version> <flags>
// set a connection pass

void PASS(User &user, Server &server)
{
	if (user.isPassChecked()){
		if (user.isRegistered())
			user.addRepliesToBuffer(ERR_ALREADYTREGISTERED(user.getNickname()));
	}
	else if (server._command.args.size() >= 1) {
		if (server.getArgs()[0].compare(server.getPassword())){
			user.addRepliesToBuffer(ERR_PASSWDMISMATCH(user.getNickname()));
			server.closeOneConnection(user);
		}
		else
			user.setPassChecked();
	}
	else
		user.addRepliesToBuffer(ERR_NEEDMOREPARAMS(server.getCommand()));
	return;
}
