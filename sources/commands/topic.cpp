#include "channel.hpp"
#include "user.hpp"
#include "server.hpp"
#include "commands.hpp"

#define CHANNEL	 	server.getArgs()
#define NEWTOPIC 	server._command.trailer

void TOPIC(User &user, Server &server){
	if (!user.isRegistered())
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
	if (server._command.trailer.empty())
		chan->sendTopic(user);
	else{
		if (!chan->isChop(user.getNickMask()))
			std::cerr << "ERR_CHANOPRIVSNEEDED (482)" << std::endl; 
		else{
			chan->setTopic(NEWTOPIC);
			chan->sendChannelMessage(createCommandMessage(user, server));			
		}

	}
}