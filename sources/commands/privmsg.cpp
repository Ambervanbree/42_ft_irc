#include "channel.hpp"
#include "user.hpp"
#include "server.hpp"
#include "commands.hpp"

#define TARGET	 	server.getArgs()[0]

//PRIVMSG <msgtarget> <text to be sent>

void	channelMessage(User &user, Server &server){
	Channel *chan = findChannel(TARGET, server);

	if (chan == NULL)
		std::cerr << "ERR_CANNOTSENDTOCHAN (404)" << std::endl;
	else if (chan->isBanned(user.getNickMask()))
		return ;
	else
		chan->sendChannelMessage(user, server, server.getTrailer().erase(0, 1));
}

void	singleMessage(User &user, Server &server){
	(void)user;
	(void)server;
	User	*recipient = findUser(TARGET, server);

	if (recipient == NULL)
		std::cerr << "nope" << std::endl;
	else
		server.sendMessage(*recipient, server.getTrailer());
}

void PRIVMSG(User &user, Server &server){
	// if (!user.isRegistered())
	// 	return ;
	if (server.getArgs().empty()){
		std::cout << "ERR_NEEDMOREPARAMS (461)" << std::endl;
		return ;		
	}
	if (TARGET[0] == '#' || TARGET[0] == '&')
		channelMessage(user, server);
	else
		singleMessage(user, server);
}