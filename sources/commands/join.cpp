#include "channel.hpp"
#include "user.hpp"
#include "server.hpp"
#include "commands.hpp"

#define ARGUMENTS 	server.getArgs()
#define CHANNELS 	server.getArgs()[0]
#define KEYS 		server.getArgs()[1]

Channel		*createChannel(std::string name, User &user, Server &server){
	return &server._channels.insert(std::make_pair(name, Channel(name, user))).first->second;
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

void 		partFromAllChannels(User &user, Server &server){
	std::map<std::string, Channel>::iterator	it 	= server._channels.begin();
	std::map<std::string, Channel>::iterator	ite = server._channels.end();
	std::map<std::string, Channel>::iterator 	chan;

	while (it != ite){
		chan = it;
		it++;
		if (chan->second.onChannel(user)){
			removeUserFromChannel(&(chan->second), user, server);
			std::string message = ":" + user.getNickname() + " PART " + chan->second.getName();
			// PRIVMSG to channel: 	message
		}
	}
}

void JOIN(User &user, Server &server)
{
	// if (!user.getRegistered())
	// 	return ;
	std::deque<std::string>	channels;
	std::deque<std::string>	keys;
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
		if (chan != NULL)
			chan->addUser(keys[i], user);
		else
			chan = createChannel(channels[i], user, server);
		// PRIVMSG to channel: 	createCommandMessage(user, server);
		if (!chan->getTopic().empty())
			chan->sendTopic(user);
		chan->sendNames(user);
	}
}
