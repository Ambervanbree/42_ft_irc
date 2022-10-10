#include "channel.hpp"
#include "user.hpp"
#include "server.hpp"
#include "commands.hpp"

#define CHANNELS 	server.getArgs()[0]
#define TOKICK	 	server.getArgs()[1]
#define COMMENT 	server._command.trailer

void	sendKickMessage(Channel &chan, User &toKick, Server &server, User &kicker){
	std::string	message = createCommandMessage(kicker, server);
	if (COMMENT.empty())
		message.append(":" + toKick.getNickname());
	chan.sendChannelMessage(message);
}

void	kickUserPerChannel(Server &server, User &user, std::deque<std::string> channels, std::deque<std::string> toKick){
	Channel	*chan 		= NULL;
	User	*userToKick;
	
	for (size_t i = 0; i < channels.size(); i++){
		chan = findChannel(channels[i], server);

		if (chan == NULL)
			std::cerr << "ERR_NOSUCHCHANNEL (403)" << std::endl;
		else if (!chan->onChannel(user))
			std::cerr << "ERR_NOTONCHANNEL (442)" << std::endl;
		else if (!chan->isChop(user.getNickMask()))
			std::cerr << "ERR_CHANOPRIVSNEEDED (482)" << std::endl;
		else{
			userToKick = findUser(toKick[i], server);

			if (!chan->onChannel(*userToKick))
				std::cerr << "ERR_USERNOTINCHANNEL (441)" << std::endl;
			else{
				removeUserFromChannel(chan, user, server);
				sendKickMessage(*chan, *userToKick, server, user);
			}
		}
	}
}

void	kickMultipleUsers(Server &server, User &user, std::string channel, std::deque<std::string> toKick){
	Channel	*chan = findChannel(channel, server);

	if (chan == NULL){
		std::cerr << "ERR_NOSUCHCHANNEL (403)" << std::endl;
		return ;
	}
	if (!chan->onChannel(user)){
		std::cerr << "ERR_NOTONCHANNEL (442)" << std::endl;
		return ;
	}
	if (!chan->isChop(user.getNickMask())){
		std::cerr << "ERR_CHANOPRIVSNEEDED (482)" << std::endl;
		return ;
	}	
	
	size_t	nrKicks 	= toKick.size();
	User	*userToKick;
	
	for (size_t i = 0; i < nrKicks; i++){
		userToKick = findUser(toKick[i], server);

		if (!chan->onChannel(*userToKick))
			std::cerr << "ERR_USERNOTINCHANNEL (441)" << std::endl;
		else{
			removeUserFromChannel(chan, user, server);
			sendKickMessage(*chan, *userToKick, server, user);
		}
	}
}

void KICK(User &user, Server &server){
	// if (!user.getRegistered())
	// 	return ;
	if (server.getArgs().size() < 2){
		std::cerr << "ERR_NEEDMOREPARAMS (461)" << std::endl;
		return ;
	}

	std::deque<std::string>	channels;
	std::deque<std::string>	toKick;
	char 					delimiter[] = ",";

	split_args(CHANNELS, delimiter, channels);
	split_args(TOKICK, delimiter, toKick);

	if (channels.size() == toKick.size())
		kickUserPerChannel(server, user, channels, toKick);
	if (channels.size() == 1 && toKick.size() > 1)
		kickMultipleUsers(server, user, channels[0], toKick);
	return ;
}