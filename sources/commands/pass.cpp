#include "user.hpp"
#include "server.hpp"

// PASS <password> <version> <flags>
// set a connection pass

void PASS(User &user, Server &server)
{
	if (user.isPassChecked()){
		if (user.isRegistered())
			user.addRepliesToBuffer(ERR_ALREADYTREGISTERED(user.getNickname()));
		return;
	}
	if (server._command.args.size() == 2)
		user.addRepliesToBuffer(ERR_NEEDMOREPARAMS(user.getNickname(), server.getCommand()));
	if (server.getArgs()[0].compare(server.getPassword()))
	{
		user.addRepliesToBuffer(ERR_PASSWDMISMATCH(user.getNickname()));
		server.closeOneConnection(user);
	}
	else
		user.setPassChecked();
}
