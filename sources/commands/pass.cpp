#include "user.hpp"
#include "server.hpp"

// PASS <password> <version> <flags>
// set a connection pass

void	PASS(User &user, Server &server)
{
	std::cout << "PASS" << std::endl;
	if (user.getPassChecked())
		return;
	(void)user;
	if (server._command.args.size() != 0 && server._command.args[0].compare(server.password)){
		std::cerr << "ERR_PASSWDMISMATCH (464)" << std::endl;
		server.closeOneConnection(user);
	}
	else
		user.setPassChecked();
}
