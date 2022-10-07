#include "server.hpp"

void Server::_setCommands()
{
	_commands["PASS"] = PASS;
	_commands["NICK"] = NICK;
	_commands["USER"] = USER;
	// _commands["PING"] = PING;
	// _commands["PONG"] = PONG;
	// _commands["ERROR"] = ERROR;			x
	// _commands["WALLOPS"] = WALLOPS; 		x
	// _commands["QUIT"] = QUIT;
	// _commands["SQUIT"] = SQUIT; 			x
	_commands["JOIN"] = JOIN;
	// _commands["OPER"] = OPER;
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
	_commands["MODE"] = MODE;
	_commands["PART"] = PART;
	_commands["TOPIC"] = TOPIC;
	_commands["NAMES"] = NAMES;
	_commands["LIST"] = LIST;
	_commands["INVITE"] = INVITE;
	_commands["KICK"] = KICK;
	// _commands["CONNECT"] = CONNECT;
	// _commands["KILL"] = KILL;
	// _commands["DIE"] = DIE;
	// _commands["RESTART"] = RESTART; 		?
}

void Server::_messageToCommandStruct(std::string message){
	std::deque<std::string> 	out;
	char 						delimiter[] = " ";

	split_args(message, delimiter, out);
	unsigned int i = 0;
	if (out[i].size() && out[i][0] == ':')
		_command.prefix = out[i++];
	if (i < out.size() && out[i].size() && out[i][0] != ':')
		_command.cmd_name = out[i++];
	while (i < out.size() && out[i].size() && out[i][0] != ':')
		_command.args.push_back(out[i++]);
	while (i < out.size() && out[i].size()){
		_command.trailer += out[i++];
		if (i != out.size())
			_command.trailer += " ";
	}
	out.clear();
	for (unsigned int i = 0; i < _command.cmd_name.size(); i++)
		_command.cmd_name[i] = std::toupper(_command.cmd_name[i]);

	std::cerr << "\n------ Command struct details -----\n";
	std::cerr << "Prefix: " << _command.prefix << std::endl;
	std::cerr << "Command_name: " << _command.cmd_name << std::endl;
	std::cerr << "Args:\n";
	for (unsigned int i = 0; i < _command.args.size(); i++)
		std::cerr << _command.args[i] << "\n";
	std::cerr << "Trailer: " << _command.trailer << std::endl <<std::endl;
}

void Server::_clearCommandStruct(){
	_command.prefix.clear();
	_command.cmd_name.clear();
	_command.args.clear();	
	_command.trailer.clear();
}

void Server::_launchCommand(User &user)
{
	std::map<std::string, command>::iterator it;
	it = _commands.find(_command.cmd_name);
	if (it != _commands.end())
		it->second(user, *this);
	else
		std::cerr << "No command found\n";
}

void Server::interpretCommand(std::string &message, User &user)
{	
	_messageToCommandStruct(message);
	_launchCommand(user);
	_clearCommandStruct();
}

void Server::_splitBuffer(std::string buffer)
{
	std::string delimiter = "\r\n";
	if (buffer.size() > 1 && buffer[buffer.size() - 2] != '\r')
		delimiter = "\n";
	split_on_string(buffer, delimiter, _bufferCommand);
	for (unsigned int i = 0; i < _bufferCommand.size(); i++)
	{
		std::cerr << "[+] split buffer [" << i << "] " << _bufferCommand[i];
		std::cerr << " -> len: " << _bufferCommand[i].size() << std::endl;
	}
}

void Server::_handleBuffer(char *buffer, User &user)
{
	user.setBuffer(std::string(buffer));
	std::string newBuffer = user.getBuffer();
	
	if (newBuffer[newBuffer.size() - 1] == '\n')
	{
		_splitBuffer(std::string(newBuffer));
		while (_bufferCommand.size())
		{
			interpretCommand(_bufferCommand[0], user);
			_bufferCommand.pop_front();
		}
		user.resetBuffer();
	}
}