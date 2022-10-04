#include "user.hpp"
#include "server.hpp"

// PASS <password> <version> <flags>
// set a connection pass

void	PASS(User &user, Server &server)
{
	std::cout << "PASS" << std::endl;
	(void)user;
	if (server._command.args[0].compare(server.password))
		std::cerr << "ERR_PASSWDMISMATCH (464)" << std::endl;
	else
		std::cerr << "Right password !" << std::endl;
	// ------> + close the connection
}
