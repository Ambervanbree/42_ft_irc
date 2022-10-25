#include "user.hpp"
#include "server.hpp"

//OPER <username> <serverpassword>
//-> Obtain operator priviliges.

void	OPER(User &user, Server &server)
{
	if (!user.isRegistered())
		return;
	if (server._command.args.size() < 2)
		user.addRepliesToBuffer(ERR_NEEDMOREPARAMS(server.getCommand()));
	else if (server._command.args[0].compare(server.getOperUsername()))
		user.addRepliesToBuffer(ERR_NOOPERHOST(user.getNickname()));
	else if (server._command.args[1].compare(server.getOperPassword()))
		user.addRepliesToBuffer(ERR_PASSWDMISMATCH(user.getNickname()));
	else {
		user.setMode('o');
		server.operators.push_back(server._command.args[0]);
		user.addRepliesToBuffer(RPL_YOUREOPER(user.getNickname()));
	}
}