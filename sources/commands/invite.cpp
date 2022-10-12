#include "channel.hpp"
#include "user.hpp"
#include "server.hpp"
#include "commands.hpp"

#define INVITEE	server.getArgs()[0]
#define CHANNEL	server.getArgs()[1]

void	sendInvite(User &inviter, Server &server){
	User	*invitee = findUser(INVITEE, server);

	if (invitee != NULL){
		(void)inviter;
		// PRIVMSG to invitee: createCommandMessage(server);
		// PRIVMSG to inviter: RPL_INVITING (341)
	}
	return ;
}

void INVITE(User &user, Server &server){
	if (!user.isRegistered())
		return ;
	if (server.getArgs().size() < 2){
		std::cerr << "ERR_NEEDMOREPARAMS (461)" << std::endl;
		return ;
	}
	Channel	*chan = findChannel(CHANNEL, server);

	if (chan != NULL){
		if (!chan->onChannel(user)){
			std::cerr << "ERR_NOTONCHANNEL (442)" << std::endl;
			return ;		
		}
		if (chan->onChannel(INVITEE)){
			std::cerr << "ERR_USERONCHANNEL (443)" << std::endl;
			return ;
		}
	}
	sendInvite(user, server);
}

/* 
	Note: 
	The RFC states that the channel does not have to exist or be
	a valid channel. However, if the channel does exist, the user inviting
	should be on the channel and the user to be invited not.
*/
