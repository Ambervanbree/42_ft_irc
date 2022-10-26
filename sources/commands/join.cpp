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
	channelWelcomeMessage(*channel, user);
	
	return channel ;
}

bool 		grammarCheckChannel(std::string name){
	if (name.size() > 50
		|| !(name[0] == '&' || name[0] == '#')
		|| name.find(',') != std::string::npos
		|| name.find(7) != std::string::npos){
		return false;
	}
	return true;
}

void JOIN(User &user, Server &server){
	if (!user.isRegistered())
		return ;
	user.newAction();
	
	std::vector<std::string>	channels;
	std::vector<std::string>	keys;
	char 						delimiter[] = ",";
	
	if (ARGUMENTS.empty()){
		user.addRepliesToBuffer(ERR_NEEDMOREPARAMS(user.getNickname(), server.getCommand()));
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
		if (!grammarCheckChannel(channels[i])){
			user.addRepliesToBuffer(ERR_BADCHANMASK(channels[i]));
			return ;
		}
		Channel	*chan = findChannel(channels[i], server);
		if (chan != NULL){
			if (keys.empty() || keys[i].empty())
				chan->addUser("", user);
			else
				chan->addUser(keys[i], user);
		}
		else
			chan = createChannel(channels[i], user, server);
	}
}
