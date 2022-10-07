#include "channel.hpp"
#include "user.hpp"
#include "server.hpp"
#include "commands.hpp"

//PART <channel>{,<channel>} [<reason>]
#define CHANNELS 	server.getArgs()[0]
#define MESSAGE 	server._command.trailer

void PART(User &user, Server &server) {
	if (!user.isRegistered())
		return ;
	if (server.getArgs().empty()){
		std::cerr << "ERR_NEEDMOREPARAMS (461)" << std::endl;
		return ;
	}

	std::deque<std::string>	channels;
	char 					delimiter[] = ",";
	Channel					*chan = NULL;

	split_args(CHANNELS, delimiter, channels);

	for (size_t i = 0; i < channels.size(); i++){
		chan = findChannel(channels[i], server);
		if (chan == NULL){
			std::cerr << "ERR_NOSUCHCHANNEL (403)" << std::endl;
			break ;
		}
		if (!chan->onChannel(user)){
			std::cerr << "ERR_NOTONCHANNEL (442)" << std::endl;
			break ;
		}
		removeUserFromChannel(chan, user, server);
		// send to channel:
		std::cout << "[+] PART message: User " << user.getNickname() << " leaving channel " << chan->getName();
		if (MESSAGE.empty())
			std::cout << std::endl;
		else
			std::cout << " with the message \"" << MESSAGE << "\"" << std::endl;
		}
}
