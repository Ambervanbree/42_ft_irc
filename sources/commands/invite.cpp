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
		//server.sendMessage(*invitee, createCommandMessage(server));
		invitee->addRepliesToBuffer(createCommandMessage(server));
		// PRIVMSG to inviter: RPL_INVITING (341)
	}
	return ;
}

void INVITE(User &user, Server &server){
	// if (!user.isRegistered())
	// 	return ;
	if (server.getArgs().size() < 2){
		user.addRepliesToBuffer(ERR_NEEDMOREPARAMS(user.getNickname(), server.getCommand()));
		return ;
	}
	Channel	*chan = findChannel(CHANNEL, server);

	if (chan != NULL){
		if (!chan->onChannel(user)){
			user.addRepliesToBuffer(ERR_NOTONCHANNEL(user.getNickname(), CHANNEL[0]));
			return ;		
		}
		if (chan->onChannel(INVITEE)){
			user.addRepliesToBuffer(ERR_USERONCHANNEL(INVITEE, CHANNEL));
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
