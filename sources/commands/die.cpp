#include "user.hpp"
#include "server.hpp"

// DIE

void	DIE(User &user, Server &server)
{
    if (!user.isRegistered())
        return;
    if (!isOperator(user.getUsername(), server))
        std::cerr << "(481) ERR_NOPRIVILEGES" << std::endl;
    server.quitServer();
}
