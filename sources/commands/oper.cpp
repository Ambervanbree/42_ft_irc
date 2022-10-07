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
		std::cerr << "(461) ERR_NEEDMOREPARAMS" << std::endl;
	// check if the username provided is the one of the user
	// and as we already checked if user was registered in the host/server
	// No need for further check
    else if (user.getUsername().compare(server._command.args[0]))
		std::cerr << "(491) ERR_NOOPERHOST" << std::endl;
	// check if user entered the right host/server password
	else if (server._command.args[1].compare(server.getPassword()))
		std::cerr << "(464) ERR_PASSWDMISMATCH" << std::endl;
	else {
		server.operators.push_back(server._command.args[0]);
		std::cout << "(381) RPL_YOUREOPER" << std::endl;
	}
}