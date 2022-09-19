#include "parser.hpp"
#include "utils.hpp"

void _setCommands()
{
	_commands["PASS"] = PASS;
	_commands["NICK"] = NICK;
	_commands["PING"] = PING;
	_commands["PONG"] = PONG;
	/*_commands["ERROR"] = ERROR;
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
	_commands["RESTART"] = RESTART;*/
}

std::vector<std::string> _splitMessage(std::string message)
{
	std::vector<std::string> out;
	char delimiter[] = " ";
	split_args(message, delimiter, out);
	if (out.size() != 0 && out[0].size() != 0 && out[0][1] == ':')
		out.erase(out.begin());
	return out;
}

void _launchCommand(std::vector<std::string> commande, User user, Channel channel)
{
	if (commande.size() == 0)
		return ;
	std::map<std::string, command>::iterator it;
	it = _commands.find(commande[1]);
	if (it != _commands.end())
		it->second(commande, user, channel);
}

void interpretCommand(std::string message, User user, Channel channel)
{
	_launchCommand(_splitMessage(message), user, channel);
}	