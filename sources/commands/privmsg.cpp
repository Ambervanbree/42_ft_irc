#include "channel.hpp"
#include "user.hpp"
#include "server.hpp"
#include "commands.hpp"

#define TARGET	 	server.getArgs()[0]

void	channelMessage(User &user, Server &server){
	Channel *chan = findChannel(TARGET, server);

	if (chan == NULL || (chan != NULL && !chan->onChannel(user)))
		std::cerr << "ERR_CANNOTSENDTOCHAN (404)" << std::endl;
	else if (chan->isBanned(user.getNickMask()))
		return ;
	else
		chan->sendChannelMessage(user, server, server.getTrailer().insert(0, " "));
}

void	singleMessage(User &user, Server &server){
	User	*recipient = findUser(TARGET, server);

	if (recipient == NULL)
		std::cerr << "ERR_NOSUCHNICK (401)" << std::endl;
	else{
		std::string message = ":" + user.getNickname() + " " + server.getTrailer() + "\n";
		server.sendMessage(*recipient, message);
	}
}

void PRIVMSG(User &user, Server &server){
	// if (!user.isRegistered())
	// 	return ;
	if (server.getArgs().empty())
		std::cerr << "ERR_NORECIPIENT (411)" << std::endl;
	else if (server.getArgs().size() > 1)
		std::cerr << "ERR_TOOMANYTARGETS (407)" << std::endl;
	else if (server.getTrailer().empty())
		std::cerr << "ERR_NOTEXTTOSEND (412)" << std::endl;
	else{
		if (TARGET[0] == '#' || TARGET[0] == '&')
			channelMessage(user, server);
		else
			singleMessage(user, server);
		// TODO -> should be able to send to server too, but not sure how to catch that.
	}
}