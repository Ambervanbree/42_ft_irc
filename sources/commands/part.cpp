#include "channel.hpp"
#include "user.hpp"
#include "server.hpp"
#include "commands.hpp"

//PART <channel>{,<channel>} [<reason>]
#define CHANNELS 	server.getArgs()[0]

void PART(User &user, Server &server)
{
	if (server.getArgs().empty()){
		std::cerr << "ERR_NEEDMOREPARAMS (461)" << std::endl;
		return ;
	}

	std::deque<std::string>	channels;
	char 					delimiter[] = ",";

	split_args(CHANNELS, delimiter, channels);

	for (size_t i = 0; i < channels.size(); i++){
		Channel	*chan = findChannel(channels[i], server);
		if (chan == NULL){
			std::cerr << "ERR_NOSUCHCHANNEL (403)" << std::endl;
			return ;
		}
		if (!chan->onChannel(user)){
			std::cerr << "ERR_NOTONCHANNEL (442)" << std::endl;
			return ;
		}
		std::cout << user.getNickname() << " removed from channel " << chan->getName() << std::endl;
		chan->removeUser(user);
		if (chan->isEmpty()){
			std::list<Channel>::iterator	it = server._channels.begin();
			for (; it != server._channels.end(); it++){
				if (it->getName() == chan->getName()){
					std::cout << "Channel " << chan->getName() << " deleted" << std::endl;
					server._channels.erase(it);
					break ;
				}
			}
		}
	}
}
