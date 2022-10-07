#include "user.hpp"
#include "server.hpp"
#include "command_utils.cpp"

// Parameters: <nickname> <comment>



void	KILL(User &user, Server &server) {
  if (!user.isRegistered())
    return;
	if (server._command.args.size() < 2)
		std::cerr << "(461) ERR_NEEDMOREPARAMS" << std::endl;
  if (!isOperator(user.getUsername(), server))
    std::cerr << "(481) ERR_NOPRIVILEGES" << std::endl;
  std::string nickname = server._command.args[0];
  User *toBeKilled = findUser(nickname, server);
  if (!toBeKilled)
    std::cerr << "(401) ERR_NOSUCHNICK" << std::endl;
  else
    server.closeOneConnection(*toBeKilled, server._command.args[1]);
}