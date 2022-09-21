#include "channel.hpp"
#include "user.hpp"
#include "server.hpp"
#include "commands.hpp"

#define CHANNELS command[1]
#define KEYS command[2]
#define CHANNEL1 channels[0]
#define CHANNEL2 channels[1]
#define KEY1 keys[0]
#define KEY2 keys[1]


Channel*	channelExists(std::string channelName, Server &server){
	std::list<Channel>::iterator	it = server._channels.begin();
	std::list<Channel>::iterator	ite = server._channels.end();

	for (; it != ite; it++){
		if ((*it).getName() == channelName)
			return &(*it);
	}
	return NULL;
}

void		createChannel(std::string name, User &user, Server &server){
	// checkChannelName(name);
	if (name.size() > 20){
		std::cerr << "ERR_BADCHANMASK (476)" << std::endl;
		std::cerr << "<channel> :Bad Channel Mask" << std::endl;
		return ;
	}
	if (name[0] != '#')
		name.insert(0, 1, '#');
	server._channels.push_back(Channel(name, user));
	// send RPL_TOPIC, RPL_NAMREPLY
}

// void		checkChannelName(std::string &name){
// }

// JOIN <channel>
// -> Check if a client is allowed to join a channel.
void JOIN(std::deque<std::string> command, User &user, Server &server)
{
	std::deque<std::string>	channels;
	std::deque<std::string>	keys;
	char 					delimiter[] = ",";
	
	split_args(CHANNELS, delimiter, channels);
	split_args(KEYS, delimiter, keys);

	for (size_t i = 0; i < channels.size(); i++){
		Channel	*chan = channelExists(channels[i], server);
		if (chan != NULL)
			chan->addUser(keys[i], user);
		else
			createChannel(channels[i], user, server);
	}
}
