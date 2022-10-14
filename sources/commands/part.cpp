#include "channel.hpp"
#include "user.hpp"
#include "server.hpp"
#include "commands.hpp"

#define CHANNELS 	server.getArgs()[0]

void PART(User &user, Server &server) {
	// if (!user.isRegistered())
	// 	return ;
	if (server.getArgs().empty()){
		std::cerr << "ERR_NEEDMOREPARAMS (461)" << std::endl;
		return ;
	}

	std::vector<std::string>	channels;
	char 					delimiter[] = ",";
	Channel					*chan = NULL;

	split_args(CHANNELS, delimiter, channels);

	for (size_t i = 0; i < channels.size(); i++){
		chan = findChannel(channels[i], server);
		if (chan == NULL)
			std::cerr << "ERR_NOSUCHCHANNEL (403)" << std::endl;
		else if (!chan->onChannel(user))
			std::cerr << "ERR_NOTONCHANNEL (442)" << std::endl;
		else{
			removeUserFromChannel(chan, user, server);
			chan->sendChannelMessage(user, server, createCommandMessage(server));			
		}

	}
}
