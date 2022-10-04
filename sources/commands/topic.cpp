#include "channel.hpp"
#include "user.hpp"
#include "server.hpp"
#include "commands.hpp"

// TOPIC <channel> [ <topic> ]

#define CHANNEL	 	server.getArgs()[0]
#define NEWTOPIC 	server.getArgs()[1]

void TOPIC(User &user, Server &server){
	if (CHANNEL.empty()){
		// ERR_NEEDMOREPARAMS 
		return ;
	}
	if (NEWTOPIC.empty()){
		Channel *chan = findChannel(CHANNEL, server);
		if (chan == NULL)
			return ;
		if (!chan->onChannel(user)){
			// ERR_NOTONCHANNEL
			return ;
		}
		// chan->sendTopic(user);
	}
	else{
		// chan->setTopic(user);
	}
}