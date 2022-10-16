#include "user.hpp"
#include "server.hpp"
// #include "command_utils.cpp"

// Parameters: <nickname> <comment>



void	KILL(User &user, Server &server) {
  if (!user.isRegistered())
    return;
  if (!isOperator(user.getUsername(), server))
    user.addRepliesToBuffer(ERR_NOPRIVILEGES);
	else if (server.getArgs().size() < 2)
    user.addRepliesToBuffer(ERR_NEEDMOREPARAMS(server.getCommand()));
  else {
    std::string designatedVictim = server.getArgs()[0];
    User *victim = findUser(designatedVictim, server);
    if (!victim)
      user.addRepliesToBuffer(ERR_NOSUCHNICK(designatedVictim));
    else {
      std::string message = "killed by " + user.getNickname() + " - reason : " + server.getArgs()[1] + "))";
      std::string hostMask = victim->getNickMask();
      server.quitMessage(hostMask, message);
      //server.errorMessage(*victim, "Closing Link: " + message);
      victim->addRepliesToBuffer(ERROR_message(message));
      server.closeOneConnection(*victim);
    }
  }
}