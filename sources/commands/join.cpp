#include "channel.hpp"
#include "user.hpp"
#include "server.hpp"
#include "commands.hpp"

#define ARGUMENTS 	server.getArgs()
#define CHANNELS 	server.getArgs()[0]
#define KEYS 		server.getArgs()[1]

Channel		*createChannel(std::string name, User &user, Server &server){
	Channel	*channel = new Channel(name, user);

	server._channels.insert(std::make_pair(name, channel));
	
	return channel ;
}

bool 		grammarCheckChannel(std::string name){
	if (name.size() > 50
		|| !(name[0] == '&' || name[0] == '#')
		|| name.find(',') != std::string::npos
		|| name.find(7) != std::string::npos){
		std::cerr << "ERR_BADCHANMASK (476)" << std::endl;
		return false;
	}
	return true;
}

void JOIN(User &user, Server &server){
// 	if (!user.isRegistered())
// 		return ;
	std::vector<std::string>	channels;
	std::vector<std::string>	keys;
	char 					delimiter[] = ",";
	
	if (ARGUMENTS.empty()){
		std::cerr << "ERR_NEEDMOREPARAMS (461)" << std::endl;
		return ;
	}
	split_args(CHANNELS, delimiter, channels);
	if (CHANNELS == "0"){
		partFromAllChannels(user, server);
		return ;
	}
	if (server.getArgs().size() > 1)
		split_args(KEYS, delimiter, keys);
	for (size_t i = 0; i < channels.size(); i++){
		if (!grammarCheckChannel(channels[i]))
			return ;
		Channel	*chan = findChannel(channels[i], server);
		if (chan != NULL){
			if (!chan->hasChop()){
				std::cout << "[-] Chan no chop" << std::endl;
				return ;
			}
			else{
				if (keys.empty())
					chan->addUser("", user);
				else
					chan->addUser(keys[i], user);
			}
		}
		else
			chan = createChannel(channels[i], user, server);
		chan->sendChannelMessage(user, server, createCommandMessage(server));
		if (!chan->getTopic().empty())
			chan->sendTopic(user);
		// chan->getNames(); will return the list of names on the channel
		// RPL send to user:
		std::cout << "RPL_NAMREPLY (353)" << std::endl;
	}
}
