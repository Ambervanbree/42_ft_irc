#include "user.hpp"
#include "server.hpp"

// Command: PONG
// Parameters: <server> [ <server2> ]

void	PONG(User &user, Server &server)
{
    if (server.getArgs().size() < 1)
        user.addRepliesToBuffer(ERR_NOORIGIN);
    else if ((server.getArgs().size() > 1) && (server.getArgs()[1].compare(user.getHostname())))
        user.addRepliesToBuffer(ERR_NOSUCHSERVER(server.getArgs()[1]));
    else
        user.newAction();
}
