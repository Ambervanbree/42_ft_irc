#include "channel.hpp"
#include "user.hpp"
#include "server.hpp"
#include "commands.hpp"

#define CHANNELS 	server.getArgs()[0]
#define TOKICK	 	server.getArgs()[1]
#define COMMENT 	server._command.trailer

void	sendKickMessage(Channel &chan, Server &server, User &kicker){
	if (COMMENT.empty())
		chan.sendChannelMessage(kicker, KICK_message(chan->getName(), TOKICK));
	else
		chan.sendChannelMessage(kicker, KICK_message_2(chan->getName(), TOKICK, COMMENT));
}

void	kickUserPerChannel(Server &server, User &user, std::vector<std::string> channels, std::vector<std::string> toKick){
	Channel	*chan 		= NULL;
	User	*userToKick;
	
	for (size_t i = 0; i < channels.size(); i++){
		chan = findChannel(channels[i], server);

		if (chan == NULL)
			user.addRepliesToBuffer(ERR_NOSUCHCHANNEL(user.getNickname(), channels[i]));
		else if (!chan->onChannel(user))
			user.addRepliesToBuffer(ERR_NOTONCHANNEL(user.getNickname(), chan->getName()));
		else if (!chan->isChop(user.getNickMask()))
			user.addRepliesToBuffer(ERR_CHANPRIVSNEEDED(user.getNickname(), chan->getName()));
		else{
			userToKick = findUser(toKick[i], server);

			if (userToKick == NULL)
				return ;
			else if (!chan->onChannel(*userToKick))
				user.addRepliesToBuffer(ERR_USERNOTINCHANNEL(userToKick->getNickname(), chan->getName()));
			else{
				removeUserFromChannel(chan, user, server);
				sendKickMessage(*chan, server, user);
			}
		}
	}
}

void	kickMultipleUsers(Server &server, User &user, std::string channel, std::vector<std::string> toKick){
	Channel	*chan = findChannel(channel, server);

	if (chan == NULL)
		user.addRepliesToBuffer(ERR_NOSUCHCHANNEL(user.getNickname(), channel));
	else if (!chan->onChannel(user))
		user.addRepliesToBuffer(ERR_NOTONCHANNEL(user.getNickname(), chan->getName()));
	else if (!chan->isChop(user.getNickMask()))
		user.addRepliesToBuffer(ERR_CHANPRIVSNEEDED(user.getNickname(), chan->getName()));
	else{
		size_t	nrKicks 	= toKick.size();
		User	*userToKick;
		
		for (size_t i = 0; i < nrKicks; i++){
			userToKick = findUser(toKick[i], server);

			if (userToKick == NULL)
				return ;
			else if (!chan->onChannel(*userToKick))
				user.addRepliesToBuffer(ERR_USERNOTINCHANNEL(userToKick->getNickname(), chan->getName()));
			else{
				removeUserFromChannel(chan, user, server);
				sendKickMessage(*chan, server, user);
			}
		}
	}
	
}

void KICK(User &user, Server &server){
	if (!user.isRegistered())
		return ;
	if (server.getArgs().size() < 2){
		user.addRepliesToBuffer(ERR_NEEDMOREPARAMS(user.getNickname(), server.getCommand()));
		return ;
	}

	std::vector<std::string>	channels;
	std::vector<std::string>	toKick;
	char 					delimiter[] = ",";

	split_args(CHANNELS, delimiter, channels);
	split_args(TOKICK, delimiter, toKick);

	if (channels.size() == toKick.size())
		kickUserPerChannel(server, user, channels, toKick);
	if (channels.size() == 1 && toKick.size() > 1)
		kickMultipleUsers(server, user, channels[0], toKick);
	return ;
}