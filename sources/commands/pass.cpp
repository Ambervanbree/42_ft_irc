#include "user.hpp"
#include "server.hpp"

// PASS <password> <version> <flags>
// set a connection pass

void	PASS(User &user, Server &server)
{
	if (user.isPassChecked() || (server._command.args.size() == 0))
		return;
	if (server._command.args[0].compare(server.getPassword())) {
		std::cerr << "ERR_PASSWDMISMATCH (464)" << std::endl;
		server.closeOneConnection(user, "\0");
	}
	else
		user.setPassChecked();
}
