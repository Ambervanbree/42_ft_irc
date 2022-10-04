#include "user.hpp"
#include "server.hpp"

// PASS <password> <version> <flags>
// set a connection pass

void	PASS(User &user, Server &server)
{
	std::cout << "PASS" << std::endl;
	(void)user;
	if (server._command.cmd_name.compare(server.password))
		std::cerr << "ERR_PASSWDMISMATCH (464)" << std::endl;
	else
		std::cout << "Right password !";
	//  Voir si le pb de non reconnaissance du pwd vient du parsing
	// ------> + close the connection
}
