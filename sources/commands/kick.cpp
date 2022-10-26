#include "channel.hpp"
#include "user.hpp"
#include "server.hpp"
#include "commands.hpp"

#define CHANNELS 	server.getArgs()[0]
#define TOKICK	 	server.getArgs()[1]
#define COMMENT 	server._command.trailer

void	sendKickMessage(Channel &chan, Server &server, User &kicker){
	if (COMMENT.size() <= 1)
		chan.sendChannelMessage(kicker, KICK_message(TOKICK, chan.getName()));
	else
		chan.sendChannelMessage(kicker, KICK_message_2(TOKICK, chan.getName(), COMMENT));
}

void	kickPerChannel(User &user, Server &server, Channel *chan, std::string toKick){
	if (!chan->onChannel(user.getNickname()))
		user.addRepliesToBuffer(ERR_NOTONCHANNEL(user.getNickname(), chan->getName()));
	else if (!chan->isChop(user.getNickMask()))
		user.addRepliesToBuffer(ERR_CHANPRIVSNEEDED(user.getUsername(),chan->getName()));
	else if(!chan->onChannel(toKick))
		user.addRepliesToBuffer(ERR_USERNOTINCHANNEL(toKick, chan->getName()));
	else{
		User	*userToKick = findUser(toKick, server);
		
		if (userToKick == NULL)
			user.addRepliesToBuffer(ERR_NOSUCHNICK(toKick));
		else{
			removeUserFromChannel(chan, *userToKick, server);
			sendKickMessage(*chan, server, user);
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

	Channel		*chan;

	if (channels.size() == toKick.size()){
		for (size_t i = 0; i < channels.size(); i++){
			chan = findChannel(channels[i], server);
			if (chan == NULL)
				user.addRepliesToBuffer(ERR_NOSUCHCHANNEL(user.getNickname(), channels[i]));
			else
				kickPerChannel(user, server, chan, toKick[i]);
		}
	}
	else if (channels.size() == 1 && toKick.size() > 1){
		chan = findChannel(channels[0], server);
		if (chan == NULL)
			user.addRepliesToBuffer(ERR_NOSUCHCHANNEL(user.getNickname(), channels[0]));
		else{
			for (size_t i = 0; i < toKick.size(); i++)
				kickPerChannel(user, server, chan, toKick[i]);
		}
	}
	return ;
}