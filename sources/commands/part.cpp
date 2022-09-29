#include "channel.hpp"
#include "user.hpp"
#include "server.hpp"
#include "commands.hpp"

//PART <channel>

void PART(std::deque<std::string> command, User &user, Server &server)
{
	if (command[1].empty()){
		std::cerr << "ERR_NEEDMOREPARAMS (461)" << std::endl;
		return ;		
	}
	Channel	*chan = findChannel(command[1], server);
	if (chan == NULL){
		std::cerr << "ERR_NOSUCHCHANNEL (403)" << std::endl;
		return ;
	}
	chan->removeUser(user);
	// if (chan->_users.size() == 0){
	// 	server._channels.erase(chan);
	// 	delete &chan;
	// }
}
