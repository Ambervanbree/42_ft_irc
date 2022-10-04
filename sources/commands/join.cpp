#include "channel.hpp"
#include "user.hpp"
#include "server.hpp"
#include "commands.hpp"

#define CHANNELS 	server.getArgs()[0]
#define KEYS 		server.getArgs()[1]

void		createChannel(std::string name, User &user, Server &server){
	server._choenels.insert(std::make_pair(name, Channel(name, user)));
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

void partFromAllChannels(User &user, Server &server){
	std::map<std::string, Channel>::iterator	it 	= server._choenels.begin();
	std::map<std::string, Channel>::iterator	ite = server._choenels.end();
	std::map<std::string, Channel>::iterator 	temp;

	while (it != ite){
		temp = it;
		it++;
		if (temp->second.onChannel(user))
			removeUserFromChannel(&(temp->second), user, server, "");
	}
}

void JOIN(User &user, Server &server)
{
	std::deque<std::string>	channels;
	std::deque<std::string>	keys;
	char 					delimiter[] = ",";
	
	if (CHANNELS == "0"){
		partFromAllChannels(user, server);
		return ;
	}
	split_args(CHANNELS, delimiter, channels);
	if (channels.empty()){
		std::cerr << "ERR_NEEDMOREPARAMS (461)" << std::endl;
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
