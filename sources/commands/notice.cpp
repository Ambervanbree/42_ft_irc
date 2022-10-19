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
		chan->sendChannelMessage(user, NOTICE_message_c(chan->getName(), server.getTrailer()));
}

void	singleNotice(User &user, Server &server){
	User	*recipient = findUser(TARGET, server);

	if (recipient == NULL)
		return ;
	else
		recipient->addRepliesToBuffer(NOTICE_message(user.getNickname(), recipient->getNickname(), server.getTrailer()));
}

void NOTICE(User &user, Server &server){
	if (!user.isRegistered())
		return ;
	if (server.getArgs().empty()
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