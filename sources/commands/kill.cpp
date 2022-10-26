#include "user.hpp"
#include "server.hpp"
// #include "command_utils.cpp"

// Parameters: <nickname> <comment>



void	KILL(User &user, Server &server) {
  if (!user.isRegistered())
    return;
  if (!isOperator(user.getUsername(), server))
    user.addRepliesToBuffer(ERR_NOPRIVILEGES(user.getNickname()));
	else if (server.getArgs().size() != 1)
    user.addRepliesToBuffer(ERR_NEEDMOREPARAMS(user.getNickname(), server.getCommand()));
  else {
    std::string designatedVictim = server.getArgs()[0];
    User *victim = findUser(designatedVictim, server);
    if (!victim)
      user.addRepliesToBuffer(ERR_NOSUCHNICK(designatedVictim));
    else {
    	std::string message = "killed by " + user.getNickname() + " - reason ";
		if (server.getTrailer().size() <= 1)
			message += ":No reason given";
		else
			message += server.getTrailer();
      	std::string hostMask = victim->getNickMask();
      	server.quitMessage(hostMask, message);
      	victim->addRepliesToBuffer(ERROR_message(message));
      	server.closeOneConnection((*victim));
    }
  }
}