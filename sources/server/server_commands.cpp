#include "server.hpp"

void Server::_setCommands()
{
	// _commands["PASS"] = PASS;
	_commands["NICK"] = NICK;
	// _commands["PING"] = PING;
	// _commands["PONG"] = PONG;
	// _commands["ERROR"] = ERROR;			x
	// _commands["WALLOPS"] = WALLOPS; 		x
	// _commands["QUIT"] = QUIT;
	// _commands["SQUIT"] = SQUIT; 			x
	_commands["JOIN"] = JOIN;
	// _commands["USER"] = USER;
	// _commands["OPER"] = OPER;
	// _commands["MODE"] = MODE;
	// _commands["SERVICE"] = SERVICE; 		x
	// _commands["PRIVMSG"] = PRIVMSG;
	// _commands["NOTICE"] = NOTICE;
	// _commands["MOTD"] = MOTD;
	// _commands["LUSERS"] = LUSERS; 		x
	// _commands["VERSION"] = VERSION; 		x
	// _commands["STATS"] = STATS; 			x
	// _commands["TIME"] = TIME; 			x
	// _commands["INFO"] = INFO; 			x
	// _commands["WHO"] = WHO; 				?
	// _commands["WHOWAS"] = WHOWAS; 		x
	// _commands["WHOIS"] = WHOIS;
	// _commands["PART"] = PART;
	// _commands["TOPIC"] = TOPIC;
	// _commands["NAMES"] = NAMES; 			x
	// _commands["LIST"] = LIST; 			x
	// _commands["INVITE"] = INVITE; 		x
	// _commands["KICK"] = KICK;
	// _commands["CONNECT"] = CONNECT;
	// _commands["KILL"] = KILL;
	// _commands["DIE"] = DIE;
	// _commands["RESTART"] = RESTART; 		?
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
		it->second(commande, user, *this);
	else
		std::cerr << "No command found\n";
}

void Server::interpretCommand(std::string &message, User &user)
{
	_launchCommand(_splitMessage(message), user);
}

void Server::_splitBuffer(char *buffer)
{
	std::cerr << "[+] Received from client: " << buffer << std::endl;
	std::string buf = buffer;
	split_on_string(buf, "\r\n", _bufferCommand);
	for (unsigned int i = 0; i < _bufferCommand.size(); i++)
	{
		std::cerr << "[+] split buffer [" << i << "] " << _bufferCommand[i];
		std::cerr << " -> len: " << _bufferCommand[i].size() << std::endl;
	}
}

void Server::_handleBuffer(char *buffer, int clientSocket)
{
	/*Placeholder of User who will be searched by socketId*/
	User user;
	(void)clientSocket;
	_splitBuffer(buffer);
	while (_bufferCommand.size())
	{
		interpretCommand(_bufferCommand[0], user);
		_bufferCommand.pop_front();
	}
}