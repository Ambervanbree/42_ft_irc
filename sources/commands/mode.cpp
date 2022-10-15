#include "channel.hpp"
#include "user.hpp"
#include "server.hpp"
#include "commands.hpp"

#define TARGET	 	server.getArgs()[0]
#define MODESTRING 	server.getArgs()[1]

struct Mode{
	Channel						*chan;
	User						*user;
	std::string					nickMask;
	std::string					modeString;
	std::string					outString;
	std::vector<std::string>	modeArg;
	std::vector<std::string>	outArg;
	int							argNr;
};

void	addMode(char toSet, Mode &mode){
	switch (toSet){
		case 'k':
			if (mode.modeArg.empty())
				mode.user->addRepliesToBuffer(ERR_NEEDMOREPARAMS(mode.user->getNickname(), "MODE"));
			else if (mode.argNr < 3){
				mode.chan->setKey(mode.modeArg[mode.argNr]);
				mode.outString += toSet;
				mode.outArg.push_back((mode.modeArg[mode.argNr]));
				mode.argNr++;
			}
			return ;
		case 'b':
			if (mode.modeArg.empty()){
				mode.user->addRepliesToBuffer(RPL_BANLIST(mode.user->getNickname(), mode.chan->getName(), mode.chan->getBannedList()));
				mode.user->addRepliesToBuffer(RPL_ENDOFBANLIST(mode.user->getNickname(), mode.chan->getName()));
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
				mode.user->addRepliesToBuffer(ERR_NEEDMOREPARAMS(mode.user->getNickname(), "MODE"));
			else if (mode.argNr < 3){
				if (!mode.chan->onChannel(mode.modeArg[mode.argNr]))
					mode.user->addRepliesToBuffer(ERR_USERNOTINCHANNEL(mode.user->getNickname(), mode.chan->getName()));
				else{
					mode.chan->addChop(mode.modeArg[mode.argNr]);
					mode.outString += toSet;
					mode.outArg.push_back((mode.modeArg[mode.argNr]));
					mode.argNr++;					
				}
			}
			return ;			
		default:
			mode.user->addRepliesToBuffer(ERR_UNKNOWNMODE(mode.user->getNickname(), toSet));
			mode.user->addRepliesToBuffer(RPL_CHANNELMODEIS(mode.user->getNickname(), mode.chan->getName(), mode.chan->getModes()));
			return ;
	}
}

void	eraseMode(char toSet, Mode &mode){
	switch (toSet){
		case 'k':
			mode.chan->unsetKey();
			mode.outString += toSet;
			return ;
		case 'b':
			if (mode.modeArg.empty())
				mode.user->addRepliesToBuffer(ERR_NEEDMOREPARAMS(mode.user->getNickname(), "MODE"));
			else if (mode.argNr < 3){
				mode.chan->unbanUser(mode.modeArg[mode.argNr]);
				mode.outString += toSet;
				mode.outArg.push_back((mode.modeArg[mode.argNr]));
				mode.argNr++;
			}
			return ;
		case 'o':
			if (mode.modeArg.empty())
				mode.user->addRepliesToBuffer(ERR_NEEDMOREPARAMS(mode.user->getNickname(), "MODE"));
			else if (mode.argNr < 3){
				mode.chan->removeChop(mode.modeArg[mode.argNr]);
				mode.outString += toSet;
				mode.outArg.push_back((mode.modeArg[mode.argNr]));
				mode.argNr++;
			}
			return ;
		default:
			mode.user->addRepliesToBuffer(ERR_UNKNOWNMODE(mode.user->getNickname(), toSet));
			mode.user->addRepliesToBuffer(RPL_CHANNELMODEIS(mode.user->getNickname(), mode.chan->getName(), mode.chan->getModes()));
			return ;
	}	
}

void	parseModeString(Mode &mode){
	std::string::iterator	it 	= mode.modeString.begin();
	std::string::iterator	ite = mode.modeString.end();

	if (!(*it == '+' || *it == '-'))
		return ;

	for (; it != ite; ){
		mode.outString += *it;
		switch (*(it++)){
			case '+':
				while (!(*it == '+' || *it == '-' || it == ite)){
					addMode(*it, mode);
					it++;
				}
			case '-':
				while (!(*it == '+' || *it == '-' || it == ite)){
					eraseMode(*it, mode);
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
		user.addRepliesToBuffer(ERR_NOSUCHCHANNEL(TARGET));
	else if (!chan->isChop(user.getNickMask()))
		user.addRepliesToBuffer(ERR_CHANPRIVSNEEDED(user.getNickname(), chan->getName()));
	else if (server.getArgs().size() < 2)
		user.addRepliesToBuffer(RPL_CHANNELMODEIS(user.getNickname(), chan->getName(), chan->getModes()));
	else{
		Mode	mode;

		fillModeStruct(mode, chan, server, &user);
		parseModeString(mode);

		std::string message(mode.outString);
		for (size_t i = 0; i < mode.outArg.size(); i++)
			message += mode.outArg[i] + " ";
		chan->sendChannelMessage(user, MODE_message(chan->getName(), message));	
	}

}

void	userMode(User &user, Server &server){
	Mode	mode;
	
	fillModeStruct(mode, NULL, server, &user);

	for (size_t i = 0; i < mode.modeString.size(); i++){
		if (mode.modeString[i] != '+' && mode.modeString[i] != '-')
			user.addRepliesToBuffer(ERR_UNKNOWNMODE(user.getNickname(), mode.modeString[i]));
	}
	return ;
}

void MODE(User &user, Server &server){
	if (!user.isRegistered())
		return ;
	if (server.getArgs().empty()){
		user.addRepliesToBuffer(ERR_NEEDMOREPARAMS(user.getNickname(), "MODE"));
		return ;		
	}
	if (TARGET[0] == '#' || TARGET[0] == '&')
		channelMode(user, server);
	else
		userMode(user, server);
}
