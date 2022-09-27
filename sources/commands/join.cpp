#include "channel.hpp"
#include "user.hpp"
#include "server.hpp"
#include "commands.hpp"

#define CHANNELS command[1]
#define KEYS command[2]

void		createChannel(std::string name, User &user, Server &server){
	server._channels.push_back(Channel(name, user));
	/* TODO --> add replies: 
		ERR_TOOMANYCHANNELS (405)
	*/
}

bool grammarCheckChannel(std::string name){
	if (name.size() > 50
		|| name[0] != '#'
		|| name.find(',') != std::string::npos){
		std::cerr << "ERR_BADCHANMASK (476)" << std::endl;
		return false;
	}
	return true;
}

void JOIN(std::deque<std::string> command, User &user, Server &server)
{
	std::deque<std::string>	channels;
	std::deque<std::string>	keys;
	char 					delimiter[] = ",";
	
	split_args(CHANNELS, delimiter, channels);
	split_args(KEYS, delimiter, keys);

	if (!channels.size()){
		std::cerr << "ERR_NEEDMOREPARAMS (461)" << std::endl;
		return ;
	}
	for (size_t i = 0; i < channels.size(); i++){
		if (!grammarCheckChannel(channels[i]))
			return ;
		Channel	*chan = findChannel(channels[i], server);
		if (chan != NULL)
			chan->addUser(keys[i], user);
		else
			createChannel(channels[i], user, server);
	}



	/* TODO --> add channel replies: 
		RPL_TOPIC (332)
		RPL_TOPICWHOTIME (333)
		RPL_NAMREPLY (353)
		RPL_ENDOFNAMES (366)

	   And error cases:
		ERR_TOOMANYCHANNELS (405) --> limit mode
		ERR_NOSUCHCHANNEL (403) --> not sure in what situation, 
			since if there's no such channel, it will be created
	*/
}
