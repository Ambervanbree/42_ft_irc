#include "user.hpp"
#include "server.hpp"

// DIE

void	DIE(User &user, Server &server)
{
    if (!user.isRegistered())
        return;
    if (!isOperator(user.getUsername(), server))
        user.addRepliesToBuffer(ERR_NOPRIVILEGES(user.getNickname()));
    else
        server.quitServer();
}
