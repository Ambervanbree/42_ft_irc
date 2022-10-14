#include "channel.hpp"
#include "user.hpp"
#include "server.hpp"
#include "commands.hpp"

#define CHANNEL	 	server.getArgs()
#define NEWTOPIC 	server._command.trailer

void TOPIC(User &user, Server &server){
	if (!user.isRegistered())
		return ;
	if (CHANNEL.empty()) {
		user.addRepliesToBuffer(ERR_NEEDMOREPARAMS(user.getNickname(), server.getCommand()));
		return ;
	}

	Channel *chan = findChannel(CHANNEL[0], server);
	
	if (chan == NULL) {
		user.addRepliesToBuffer(ERR_NOSUCHCHANNEL(CHANNEL[0]));
		return ;
	}
	if (!chan->onChannel(user)) {
		user.addRepliesToBuffer(ERR_NOTONCHANNEL(user.getNickname(), CHANNEL[0]));
		return ;
	}
	if (server._command.trailer.empty())
		chan->sendTopic(user);
	else{
		if (!chan->isChop(user.getNickMask()))
			user.addRepliesToBuffer(ERR_CHANPRIVSNEEDED(user.getNickname(), CHANNEL[0]));
		else{
			chan->setTopic(NEWTOPIC);
			chan->sendChannelMessage(user, TOPIC_message(chan->getName(), chan->getTopic()));
		}
	}
}