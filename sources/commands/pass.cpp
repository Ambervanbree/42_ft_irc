#include "user.hpp"
#include "server.hpp"

// PASS <password> <version> <flags>
// set a connection pass

void	PASS(User &user, Server &server)
{
	if (user.isPassChecked() || (server._command.args.size() == 0))
		return;
	if (server.getArgs()[0].compare(server.getPassword())) {
		std::cerr << "ERR_PASSWDMISMATCH (464)" << std::endl;
		// std::cerr << "server._command.args[0] = " << server._command.args[0] << std::endl;
		// std::cerr << "server.getPassword() = " << server.getPassword() << std::endl;
		server.closeOneConnection(user);
	}
	else
		user.setPassChecked();
}
