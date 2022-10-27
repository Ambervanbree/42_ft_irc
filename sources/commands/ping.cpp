#include "user.hpp"
#include "server.hpp"

// Command: PING
// Parameters: <server1>

void	PING(User &user, Server &server)
{
    if (!user.isRegistered())
		return ;
    if (server.getArgs().size() < 1)
        user.addRepliesToBuffer(ERR_NOORIGIN);
    else if ((server.getArgs().size() > 1) && (server.getArgs()[1].compare(user.getHostname())))
        user.addRepliesToBuffer(ERR_NOSUCHSERVER(server.getArgs()[1]));
    else
        user.addRepliesToBuffer(PONG_message(user.getHostname()));
}
