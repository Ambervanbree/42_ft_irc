#include "channel.hpp"
#include "user.hpp"
#include "server.hpp"
#include "commands.hpp"

#define TARGET	 	server.getArgs()[0]

void	channelNotice(User &user, Server &server){
	Channel *chan = findChannel(TARGET, server);

	if (chan == NULL 
		|| (chan != NULL && !chan->onChannel(user))
		|| chan->isBanned(user.getNickMask()))
		return ;
	else
		chan->sendChannelMessage(user, server, server.getTrailer().insert(0, " "));
}

void	singleNotice(User &user, Server &server){
	User	*recipient = findUser(TARGET, server);

	if (recipient == NULL)
		return ;
	else{
		std::string message = ":" + user.getNickname() + " " + server.getTrailer() + "\n";
		server.sendMessage(*recipient, message);
	}
}

void NOTICE(User &user, Server &server){
	(void)user;
	(void)server;
	if (!user.isRegistered() 
		|| server.getArgs().empty()
		|| server.getArgs().size() > 1
		|| server.getTrailer().empty())
		return ;
	else{
		if (TARGET[0] == '#' || TARGET[0] == '&')
			channelNotice(user, server);
		else
			singleNotice(user, server);
		// TODO -> should be able to send to server too, but not sure how to catch that.
	}
}