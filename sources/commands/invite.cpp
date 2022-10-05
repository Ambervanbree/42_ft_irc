#include "channel.hpp"
#include "user.hpp"
#include "server.hpp"
#include "commands.hpp"

// INVITE <nickname> <channel>

<<<<<<< HEAD
#define INVITEE	server.getArgs()[0]
#define CHANNEL	server.getArgs()[1]

void	sendInvite(User &inviter, Server &server){
	std::list<User>::iterator	it	= server.users.begin();
	std::list<User>::iterator	ite	= server.users.end();
	User						*invitee = NULL;

	for (; it != ite; it++){
		if (it->getNickname() == INVITEE)
			invitee = &(*it);
	}
	// Sent to invitee:
	(void)invitee;
	std::cout << "[+] INVITE message: invited to " << CHANNEL << " by " << inviter.getNickname() << std::endl;
	// Sent to inviter:
	std::cout << "RPL_INVITING (341)" << std::endl;
}

void INVITE(User &user, Server &server){
	if (!user.getRegistered())
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
=======
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
>>>>>>> 3510727 (first version invite)
