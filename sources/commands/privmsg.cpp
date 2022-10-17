#include "channel.hpp"
#include "user.hpp"
#include "server.hpp"
#include "commands.hpp"

#define TARGET	 	server.getArgs()[0]

void	channelMessage(User &user, Server &server){
	Channel *chan = findChannel(TARGET, server);

	if (chan == NULL || (chan != NULL && !chan->onChannel(user)))
		user.addRepliesToBuffer(ERR_CANNOTSENDTOCHAN(TARGET));
	else if (chan->isBanned(user.getNickMask()))
		return ;
	else
		chan->sendChannelMessage(user, PRIVMSG_message_c(chan->getName(), server.getTrailer()));
}

void	singleMessage(User &user, Server &server){
	User	*recipient = findUser(TARGET, server);

	if (recipient == NULL)
		user.addRepliesToBuffer(ERR_NOSUCHNICK(TARGET));
	else
		recipient->addRepliesToBuffer(PRIVMSG_message(user.getNickname(), recipient->getNickname(), server.getTrailer()));
}

void PRIVMSG(User &user, Server &server){
	if (!user.isRegistered())
		return ;
	user.newAction();
	if (server.getArgs().empty())
		user.addRepliesToBuffer(ERR_NORECIPIENT);
	else if (server.getArgs().size() > 1)
		user.addRepliesToBuffer(ERR_TOOMANYTARGETS);
	else if (server.getTrailer().empty())
		user.addRepliesToBuffer(ERR_NOTEXTTOSEND);
	else{
		if (TARGET[0] == '#' || TARGET[0] == '&')
			channelMessage(user, server);
		else
			singleMessage(user, server);
		// TODO -> should be able to send to server too, but not sure how to catch that.
	}
}