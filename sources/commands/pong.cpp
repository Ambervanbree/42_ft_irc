#include "user.hpp"
#include "server.hpp"

// Command: PONG
// Parameters: : <server>

void	PONG(User &user, Server &server)
{
    if (server.getTrailer().empty())
        user.addRepliesToBuffer(ERR_NOORIGIN);
    else if ((server.getArgs().size() > 0) && (server.getTrailer().compare(":" + user.getHostname())))
        user.addRepliesToBuffer(ERR_NOSUCHSERVER(server.getTrailer()));
    else
        user.newAction();
}
