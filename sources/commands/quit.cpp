#include "user.hpp"
#include "server.hpp"

// QUIT [ <reason> ]

void	QUIT(User &user, Server &server)
{
    std::string leaver = user.getNickMask();
	server.closeOneConnection(user);
    if (!server.getArgs().empty())
        server.quitMessage(leaver, server.getArgs()[0]);
    else
    {
        std::string toSend = "No reason given";
        server.quitMessage(leaver, toSend);
    }
}
