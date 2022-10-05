#include "channel.hpp"
#include "user.hpp"
#include "server.hpp"
#include "commands.hpp"

// INVITE <nickname> <channel>

void INVITE(User &user, Server &server){
	if (server.getArgs().size() < 3){
		std::cerr << "ERR_NEEDMOREPARAMS (461)" << std::endl;
		return ;
	}
	Channel	*chan = findChannel(server.getArgs()[1], server);
	if (chan == NULL){
		std::cerr << "ERR_NOSUCHCHANNEL (403)" << std::endl;
		return ;		
	}
	if (!chan->onChannel(user)){
		std::cerr << "ERR_NOTONCHANNEL (442)" << std::endl;
		return ;		
	}
	if (chan->onChannel(server.getArgs()[0])){
		std::cerr << "ERR_USERONCHANNEL (443)" << std::endl;
		return ;
	}
	chan->sendInvite(server.getArgs()[0], user);
}