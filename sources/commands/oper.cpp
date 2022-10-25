#include "user.hpp"
#include "server.hpp"

//OPER <username> <serverpassword>
//-> Obtain operator priviliges.

void	OPER(User &user, Server &server)
{
	// check if user is registered
	if (!user.isRegistered())
		return;
	// check if right number of arguments
	if (server._command.args.size() < 2)
		user.addRepliesToBuffer(ERR_NEEDMOREPARAMS(server.getCommand()));
	// check if the username provided is the one of the user
	// and as we already checked if user was registered in the host/server
	// No need for further check
    else if (user.getUsername().compare(server._command.args[0]))
		user.addRepliesToBuffer(ERR_NOOPERHOST(user.getNickname()));
	// check if user entered the right host/server password
	else if (server._command.args[1].compare(server.getOperPassword()))
		user.addRepliesToBuffer(ERR_PASSWDMISMATCH(user.getNickname()));
	else {
		user.setMode('o');
		server.operators.push_back(server._command.args[0]);
		user.addRepliesToBuffer(RPL_YOUREOPER(user.getNickname()));
	}
}