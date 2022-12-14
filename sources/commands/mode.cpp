#include "channel.hpp"
#include "user.hpp"
#include "server.hpp"
#include "commands.hpp"

#define TARGET	 	server.getArgs()[0]
#define MODESTRING 	server.getArgs()[1]

struct Mode{
	Channel						*chan;
	User						*user;
	Server						*server;
	std::string					nickMask;
	std::string					modeString;
	std::string					outString;
	std::vector<std::string>	modeArg;
	std::vector<std::string>	outArg;
	int							argNr;
};

void	addChanMode(char toSet, Mode &mode, std::string &username){
	std::string cmd_name = "MODE";
	switch (toSet){
		case 'k':
			if (mode.modeArg.empty())
				mode.user->addRepliesToBuffer(ERR_NEEDMOREPARAMS(username, cmd_name));
			else if (mode.argNr < 3){
				mode.chan->setKey(mode.modeArg[mode.argNr]);
				mode.outString += toSet;
				mode.outArg.push_back((mode.modeArg[mode.argNr]));
				mode.argNr++;
			}
			return ;
		case 'b':
			if (mode.modeArg.empty()){
				mode.user->addRepliesToBuffer(RPL_BANLIST(mode.chan->getName(), mode.chan->getBannedList()));
				mode.user->addRepliesToBuffer(RPL_ENDOFBANLIST(mode.chan->getName()));
				return ;
			}
			if (mode.argNr < 3){
				mode.chan->banUser(mode.modeArg[mode.argNr]);
				mode.outString += toSet;
				mode.outArg.push_back((mode.modeArg[mode.argNr]));
				mode.argNr++;
			}
			return ;
		case 'o':
			if (mode.modeArg.empty())
				mode.user->addRepliesToBuffer(ERR_NEEDMOREPARAMS(username, cmd_name));
			else if (mode.argNr < 3){
				if (!mode.chan->onChannel(mode.modeArg[mode.argNr]))
					mode.user->addRepliesToBuffer(ERR_USERNOTINCHANNEL(mode.user->getNickname(), mode.chan->getName()));
				else{
					User *newChop = findUser(mode.modeArg[mode.argNr], *mode.server);
					if (newChop == NULL)
						mode.user->addRepliesToBuffer(ERR_NOSUCHNICK(mode.modeArg[mode.argNr]));
					else
						mode.chan->addChop(newChop->getNickMask());
					mode.outString += toSet;
					mode.outArg.push_back((mode.modeArg[mode.argNr]));
					mode.argNr++;					
				}
			}
			return ;
		default:
			std::string newMode;
			newMode += toSet;
			mode.user->addRepliesToBuffer(ERR_UNKNOWNMODE(newMode));
			mode.user->addRepliesToBuffer(RPL_CHANNELMODEIS(username, mode.chan->getName(), mode.chan->getModes()));
			return ;
	}
}

void	eraseChanMode(char toSet, Mode &mode, std::string &username){
	std::string cmd_name = "MODE";
	switch (toSet){
		case 'k':
			mode.chan->unsetKey();
			mode.outString += toSet;
			return ;
		case 'b':
			if (mode.modeArg.empty())
				mode.user->addRepliesToBuffer(ERR_NEEDMOREPARAMS(username, cmd_name));
			else if (mode.argNr < 3){
				mode.chan->unbanUser(mode.modeArg[mode.argNr]);
				mode.outString += toSet;
				mode.outArg.push_back((mode.modeArg[mode.argNr]));
				mode.argNr++;
			}
			return ;
		case 'o':
			if (mode.modeArg.empty())
				mode.user->addRepliesToBuffer(ERR_NEEDMOREPARAMS(username, cmd_name));
			else if (mode.argNr < 3){
				User *newChop = findUser(mode.modeArg[mode.argNr], *mode.server);
				if (newChop == NULL)
					mode.user->addRepliesToBuffer(ERR_NOSUCHNICK(mode.modeArg[mode.argNr]));
				else
					mode.chan->removeChop(newChop->getNickMask());
				mode.outString += toSet;
				mode.outArg.push_back((mode.modeArg[mode.argNr]));
				mode.argNr++;
			}
			return ;
		default:
			std::string newMode;
			newMode += toSet;
			mode.user->addRepliesToBuffer(ERR_UNKNOWNMODE(newMode));
			mode.user->addRepliesToBuffer(RPL_CHANNELMODEIS(username, mode.chan->getName(), mode.chan->getModes()));
			return ;
	}	
}

void	parseChanModeString(Mode &mode, std::string &username){
	std::string::iterator	it 	= mode.modeString.begin();
	std::string::iterator	ite = mode.modeString.end();

	if (!(*it == '+' || *it == '-'))
		return ;

	for (; it != ite; ){
		mode.outString += *it;
		switch (*(it++)){
			case '+':
				while (!(*it == '+' || *it == '-' || it == ite)){
					addChanMode(*it, mode, username);
					it++;
				}
			case '-':
				while (!(*it == '+' || *it == '-' || it == ite)){
					eraseChanMode(*it, mode, username);
					it++;
				}
		}
		if (it == ite)
			return ;
	}
	return ;
}

void	addUserMode(char toSet, Mode &mode, User &user){
	std::string	newMode;
	if (toSet == 'i'){
		mode.user->setMode(toSet);
		mode.outString += toSet;
	}
	else
		mode.user->addRepliesToBuffer(ERR_UMODEUNKNOWMFLAG(user.getNickname()));
}

void	eraseUserMode(char toSet, Mode &mode, Server &server, User &user){
	std::string newMode;
	if (toSet == 'i' || toSet == 'o'){
		mode.user->unsetMode(toSet);
		mode.outString += toSet;
		if (toSet == 'o'){
			std::list<std::string>::iterator	it = server.operators.begin();
			std::list<std::string>::iterator	ite = server.operators.end();

			for (; it != ite; it++){
				if (*it == mode.user->getNickname()){
					server.operators.erase(it);
					break ;
				}
			}
		}
	}
	else
		mode.user->addRepliesToBuffer(ERR_UMODEUNKNOWMFLAG(user.getNickname()));
}

void	parseUserModeString(Mode &mode, Server &server, User &user){
	std::string::iterator	it 	= mode.modeString.begin();
	std::string::iterator	ite = mode.modeString.end();

	if (!(*it == '+' || *it == '-'))
		return ;

	for (; it != ite; ){
		mode.outString += *it;
		switch (*(it++)){
			case '+':
				while (!(*it == '+' || *it == '-' || it == ite)){
					addUserMode(*it, mode, user);
					it++;
				}
			case '-':
				while (!(*it == '+' || *it == '-' || it == ite)){
					eraseUserMode(*it, mode, server, user);
					it++;
				}
		}
		if (it == ite)
			return ;
	}
	return ;
}

void	fillModeStruct(Mode &mode, Channel *channel, Server &server, User *user){
	mode.chan			= channel;
	mode.server			= &server;
	mode.user			= user;
	mode.modeString 	= MODESTRING;
	mode.argNr			= 0;
	size_t args 		= server.getArgs().size() - 2;
	std::string			temp;

	for (size_t i = 0; i < args; i++){
		temp = server.getArgs()[i+2];
		if (temp[0] == '+' || temp[0] == '-')
			mode.modeString.append(temp);
		else
			mode.modeArg.push_back(temp);
	}
}

void	channelMode(User &user, Server &server){
	Channel		*chan = findChannel(TARGET, server);

	if (chan == NULL)
		user.addRepliesToBuffer(ERR_NOSUCHCHANNEL(user.getUsername(), TARGET));
	else if (server.getArgs().size() < 2)
		user.addRepliesToBuffer(RPL_CHANNELMODEIS(user.getNickname(), chan->getName(), chan->getModes()));
	else if (!chan->isChop(user.getNickMask()))
		user.addRepliesToBuffer(ERR_CHANPRIVSNEEDED(user.getUsername(),chan->getName()));
	else{
		Mode	mode;
		std::string username = user.getNickname();

		fillModeStruct(mode, chan, server, &user);
		parseChanModeString(mode, username);

		std::string message(mode.outString);
		for (size_t i = 0; i < mode.outArg.size(); i++)
			message += " " + mode.outArg[i] + " ";
		if (message.size() > 1)
			chan->sendChannelMessage(user, MODE_message_2(user.getNickname(), chan->getName(), message));	
	}

}

void	userMode(User &user, Server &server){
	Mode	mode;
	User	*found = findUser(TARGET, server);
	
	if (found == NULL)
		user.addRepliesToBuffer(ERR_NOSUCHNICK(user.getNickname()));
	else if (user.getNickname() != found->getNickname())
		user.addRepliesToBuffer(ERR_USERSDONTMATCH(user.getUsername()));
	else if (server.getArgs().size() < 2)
		user.addRepliesToBuffer(RPL_UMODEIS(user.getNickname(), user.getModes()));
	else{
		fillModeStruct(mode, NULL, server, &user);
		parseUserModeString(mode, server, user);
		std::string message(mode.outString);
		for (size_t i = 0; i < mode.outArg.size(); i++)
			message += " " + mode.outArg[i] + " ";
		user.addRepliesToBuffer(RPL_UMODEIS(user.getNickname(), user.getModes()));
	}
}

void MODE(User &user, Server &server){

	if (!user.isRegistered())
		return ;
	if (server.getArgs().empty()){
		user.addRepliesToBuffer(ERR_NEEDMOREPARAMS(user.getNickname(), server.getCommand()));
		return ;		
	}
	if (TARGET[0] == '#' || TARGET[0] == '&')
		channelMode(user, server);
	else
		userMode(user, server);
}
