#include "channel.hpp"
#include "user.hpp"
#include "server.hpp"
#include "commands.hpp"

void	sendWhoIs(User &user, Server &server, std::string nick){
	User *target = findUser(nick, server);

	if (target == NULL)
		user.addRepliesToBuffer(ERR_NOSUCHNICK(nick));
	else{
		user.addRepliesToBuffer(RPL_WHOISUSER(user.getNickname(), nick, target->getUsername(), target->getRealname()));
		user.addRepliesToBuffer(RPL_WHOISSERVER(user.getNickname(), nick, "localhost", "host of ACC Power network"));
		if (isOperator(nick, server))
			user.addRepliesToBuffer(RPL_WHOISOPERATOR(user.getNickname(), nick));
		user.addRepliesToBuffer(RPL_WHOISIDLE(user.getNickname(), nick, toString(target->getIdle())));
		user.addRepliesToBuffer(RPL_ENDOFWHOIS(user.getNickname(), nick));
	}
}

void WHOIS(User &user, Server &server){
	if (!user.isRegistered())
		return ;

	std::string nick;

	if (server.getArgs().size() == 0){
		user.addRepliesToBuffer(ERR_NONICKNAMEGIVEN);
		return ;
	}
	else if (server.getArgs().size() == 2){
		if (server.getArgs()[0] != "localhost" && server.getArgs()[0] != "127.0.0.1"){
			user.addRepliesToBuffer(ERR_NOSUCHSERVER(server.getArgs()[0]));
			return ;
		}
		nick = server.getArgs()[1];
	}
	else
		nick = server.getArgs()[0];
	
	sendWhoIs(user, server, nick);
}