#include "user.hpp"
#include "server.hpp"
#include "command_utils.cpp"

// Parameters: <nickname> <comment>

void	KILL(User &user, Server &server) {
  if (!user.isRegistered())
    return;
  if (!isOperator(user.getUsername(), server))
    return;
	if (server._command.args.size() < 2)
		std::cerr << "(461) ERR_NEEDMOREPARAMS" << std::endl;
    
}