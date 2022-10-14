#include "user.hpp"
#include "server.hpp"

// QUIT [ <reason> ]

void	QUIT(User &user, Server &server)
{
	server.closeOneConnection(user);
    if (!server.getArgs().empty())
        server.quitMessage(user, server.getArgs()[0]);
    else
        server.quitMessage(user, "No reason risen");
}
