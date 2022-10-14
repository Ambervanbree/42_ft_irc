#include "user.hpp"
#include "server.hpp"
// #include "command_utils.cpp"

// Parameters: <nickname> <comment>



void	KILL(User &user, Server &server) {
  if (!user.isRegistered())
    return;
  if (!isOperator(user.getUsername(), server))
    std::cerr << "(481) ERR_NOPRIVILEGES" << std::endl;
	else if (server.getArgs().size() < 2)
		std::cerr << "(461) ERR_NEEDMOREPARAMS" << std::endl;
  else {
    std::string designatedVictim = server.getArgs()[0];
    User *victim = findUser(designatedVictim, server);
    if (!victim)
      std::cerr << "(401) ERR_NOSUCHNICK" << std::endl;
    else {
      std::string message = "Killed (" + user.getNickname() + " (" + server.getArgs()[1] + "))";
      server.quitMessage(user, message);
      server.errorMessage(*victim, "Closing Link: " + message);
      server.closeOneConnection(*victim);
    }
  }
}