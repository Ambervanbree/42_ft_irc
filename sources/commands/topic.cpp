#include "channel.hpp"
#include "user.hpp"
#include "server.hpp"
#include "commands.hpp"

// TOPIC <channel> [ <topic> ]

#define CHANNEL	 	server.getArgs()
#define NEWTOPIC 	server._command.trailer

void TOPIC(User &user, Server &server){
	if (!user.getRegistered())
		return ;
	if (CHANNEL.empty()){
		std::cerr << "ERR_NEEDMOREPARAMS (461)" << std::endl; 
		return ;
	}
	Channel *chan = findChannel(CHANNEL[0], server);
	if (chan == NULL){
		std::cerr << "ERR_NOSUCHCHANNEL (403)" << std::endl; 
		return ;		
	}
	if (!chan->onChannel(user)){
		std::cerr << "ERR_NOTONCHANNEL (442)" << std::endl; 
		return ;
	}
	if (!server._command.trailer.empty())
		chan->sendTopic(user);
	else
		chan->setTopic(NEWTOPIC, user.getNickMask());
}