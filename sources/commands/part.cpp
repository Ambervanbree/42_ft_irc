#include "channel.hpp"
#include "user.hpp"
#include "server.hpp"
#include "commands.hpp"

#define CHANNELS 	server.getArgs()[0]

void PART(User &user, Server &server) {
	if (!user.isRegistered())
		return ;
	if (server.getArgs().empty()){
		user.addRepliesToBuffer(ERR_NEEDMOREPARAMS(user.getNickname(), server.getCommand()));
		return ;
	}

	std::vector<std::string>	channels;
	char 					delimiter[] = ",";
	Channel					*chan = NULL;

	split_args(CHANNELS, delimiter, channels);

	for (size_t i = 0; i < channels.size(); i++){
		chan = findChannel(channels[i], server);
		if (chan == NULL)
			user.addRepliesToBuffer(ERR_NOSUCHCHANNEL(user.getNickname(), channels[i]));
		else if (!chan->onChannel(user))
			user.addRepliesToBuffer(ERR_NOTONCHANNEL(user.getNickname(), chan->getName()));
		else{
			if (server.getTrailer().empty())
				chan->sendChannelMessage(user, PART_message(chan->getName()));
			else
				chan->sendChannelMessage(user, PART_message_2(chan->getName(), server.getTrailer()));	
			removeUserFromChannel(chan, user, server);
		}
	}
}
