#include "user.hpp"
#include "server.hpp"

// NICK <nickname>

int	wrongGrammar(const std::string &nick) {
	char forbidden[] = {' ', ',', '*', '?', '!', '@', '.'};
	char wrongStart[] = {'&', ':', '#'};
	unsigned long i = 0;

	if (nick.length() > 9)
		return 1;
	if ((nick[0] == wrongStart[0]) || nick[0] == wrongStart[1]
		|| nick[0] == wrongStart[2])
		return 1;
	for(; i < sizeof(forbidden); i++) {
		if (nick.find(forbidden[i]) != std::string::npos)
			return 1;
	}
	return 0;
}

int	existingNick(const std::string &nick, Server &server) {
	std::list<User>::iterator	ite;

	for(ite = server.users.begin(); ite != server.users.end(); ite++){
		if ((*ite).getNickname().compare(nick) == 0)
			return 1;
	}
	return 0;
}

void NICK(User &user, Server &server)
{
	if (user.isPassChecked() == false)
		return;
	if (server.getArgs().empty()) {
		user.addRepliesToBuffer(ERR_NONICKNAMEGIVEN(user.getNickname()));
		return;
	}
	std::string nick = server.getArgs()[0];
	if (wrongGrammar(nick))
		user.addRepliesToBuffer(ERR_ERRONEUSNICKNAME(nick));
	else {
		if (existingNick(nick, server)) {
			user.addRepliesToBuffer(ERR_NICKNAMEINUSE(user.getNickname(), nick));
			nick = "x";
		}
		server.nickMessage(user.getPrefix(), nick);
		std::map<std::string, Channel *>::iterator it = server._channels.begin();

		for (; it != server._channels.end(); it++) {
			if (it->second->isChop(user.getNickMask())){
				it->second->removeChop(user.getNickMask());
				it->second->addChop(nick + "!" + user.getUsername() + "@" + user.getHostname());
			}
			if (it->second->isBanned(user.getNickname())){
				it->second->unbanUser(user.getNickname());
				it->second->banUser(nick);
			}
		}
		if (user.isOperator()) {
			std::list<std::string>::iterator it = server.operators.begin();
			for (; it != server.operators.end(); it++)
			{
				if ((*it).compare(user.getNickname()) == 0){
					server.operators.erase(it);
					break;
				}
			}
			server.operators.push_back(nick);
		}
		user.setNickname(nick);
	}
	return;
}
