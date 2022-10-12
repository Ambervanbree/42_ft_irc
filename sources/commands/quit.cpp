#include "user.hpp"
#include "server.hpp"

// QUIT [ <Quit Message> ]

void	QUIT(User &user, Server &server)
{
	server.closeOneConnection(user);
    server.updateFdsStructure();
    std::cerr << user.getNickMask() << " " << server._command.cmd_name;
	if (!server._command.trailer.size())
        std::cerr << " " << server._command.trailer;
    std::cerr << std::endl;
}
