#include "server.hpp"

void Server::_setCommands()
{
	_commands["PASS"] = PASS;
	_commands["NICK"] = NICK;
	_commands["PING"] = PING;
	_commands["PONG"] = PONG;
	_commands["ERROR"] = ERROR;
	_commands["WALLOPS"] = WALLOPS;
	_commands["QUIT"] = QUIT;
	_commands["SQUIT"] = SQUIT;
	_commands["JOIN"] = JOIN;
	_commands["USER"] = USER;
	_commands["OPER"] = OPER;
	_commands["MODE"] = MODE;
	_commands["SERVICE"] = SERVICE;
	_commands["PRIVMSG"] = PRIVMSG;
	_commands["NOTICE"] = NOTICE;
	_commands["MOTD"] = MOTD;
	_commands["LUSERS"] = LUSERS;
	_commands["VERSION"] = VERSION;
	_commands["STATS"] = STATS;
	_commands["TIME"] = TIME;
	_commands["INFO"] = INFO;
	_commands["WHO"] = WHO;
	_commands["WHOWAS"] = WHOWAS;
	_commands["WHOIS"] = WHOIS;
	_commands["PART"] = PART;
	_commands["TOPIC"] = TOPIC;
	_commands["NAMES"] = NAMES;
	_commands["LIST"] = LIST;
	_commands["INVITE"] = INVITE;
	_commands["KICK"] = KICK;
	_commands["CONNECT"] = CONNECT;
	_commands["KILL"] = KILL;
	_commands["DIE"] = DIE;
	_commands["RESTART"] = RESTART;
}

std::deque<std::string> Server::_splitMessage(std::string message)
{
	std::deque<std::string> out;
	char delimiter[] = " ";
	split_args(message, delimiter, out);
	return out;
}

void Server::_launchCommand(std::deque<std::string> commande, User &user)
{
	if (commande.size() == 0)
		return ;
	int index = 0;
	if (commande[0].size() != 0 && commande[0][0] == ':')
		index = 1;
	std::map<std::string, command>::iterator it;
	it = _commands.find(commande[index]);
	if (it != _commands.end())
		it->second(commande, user);
	else
		std::cerr << "No command found\n";
}

void Server::interpretCommand(std::string &message, User &user)
{
	_launchCommand(_splitMessage(message), user);
}

