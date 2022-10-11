#include "commands.hpp"

/*Server commands*/

//PING <server1> [ <server2> ]
//-> Test the presence of an acive client or server.
void PING(std::deque<std::string> Command, User &User)
{
	(void)Command;
	(void)User;
	std::cout << "PING" << std::endl;
}

//PONG <server> [ <server2> ]
//-> Reply to a ping message.
void PONG(std::deque<std::string> Command, User &User)
{
	(void)Command;
	(void)User;
	std::cout << "PONG" << std::endl;
}

//ERROR <error message>
//-> Report a serious or fatal error to server's peers.
void ERROR(std::deque<std::string> Command, User &User)
{
	(void)Command;
	(void)User;
	std::cout << "ERROR" << std::endl;
}

//WALLOPS <Text to be sent>
//-> Send a message to all users that have set 'w' mode.
void WALLOPS(std::deque<std::string> Command, User &User)
{
	(void)Command;
	(void)User;
	std::cout << "WALLOPS" << std::endl;
}

//QUIT [<Quit Message>]
//-> Close the connection of a client and send quit message.
void QUIT(std::deque<std::string> Command, User &User)
{
	(void)Command;
	(void)User;
	std::cout << "QUIT" << std::endl;
}

//SQUIT <server> <comment>
//-> Break remote server link. 
void SQUIT(std::deque<std::string> Command, User &User)
{
	(void)Command;
	(void)User;
	std::cout << "SQUIT" << std::endl;
}

/*User commands:*/

//SERVICE <nickname> <reserved> <distribution> <type> <reserved> <info>
//-> Register a new service
void SERVICE(std::deque<std::string> Command, User &User)
{
	(void)Command;
	(void)User;
	std::cout << "SERVICE" << std::endl;
}

//QUIT [ <Quit Message> ]
//-> Client session is terminated.
/*void QUIT(std::deque<std::string> Command, User &User)
{
	(void)Command;
	(void)User;
	std::cout << "QUIT" << std::endl;
}*/

//PRIVMSG <msgtarget> <text to be sent>
//-> Send a private message to another user or to a channel.
void PRIVMSG(std::deque<std::string> Command, User &User)
{
	(void)Command;
	(void)User;
	std::cout << "PRIVMSG" << std::endl;
}

//NOTICE <msgtarget> <text>
//-> Same as PRIVMSG, but no automatic replies will be sent in response.
void NOTICE(std::deque<std::string> Command, User &User)
{
	(void)Command;
	(void)User;
	std::cout << "NOTICE" << std::endl;
}

//MOTD [ <target> ]
//-> Message of the day from a server.
void MOTD(std::deque<std::string> Command, User &User)
{
	(void)Command;
	(void)User;
	std::cout << "MOTD" << std::endl;
}

//LUSERS [ <mask> [ <target> ] ]
//-> Get statistics on the size of the IRC network. 
void LUSERS(std::deque<std::string> Command, User &User)
{
	(void)Command;
	(void)User;
	std::cout << "LUSERS" << std::endl;
}

//VERSION [ <target> ]
//-> Query version of the server program.
void VERSION(std::deque<std::string> Command, User &User)
{
	(void)Command;
	(void)User;
	std::cout << "VERSION" << std::endl;
}

//STATS [ <query> [ <target> ] ]
//-> Query statistics of the server.
void STATS(std::deque<std::string> Command, User &User)
{
	(void)Command;
	(void)User;
	std::cout << "STATS" << std::endl;
}

//TIME [ <target> ]
//-> Query local time from (specified) server.
void TIME(std::deque<std::string> Command, User &User)
{
	(void)Command;
	(void)User;
	std::cout << "TIME" << std::endl;
}

//INFO [ <target> ]
//-> Information describing the server.
void INFO(std::deque<std::string> Command, User &User)
{
	(void)Command;
	(void)User;
	std::cout << "INFO" << std::endl;
}

//WHO [ <mask> [ "o" ] ]
//-> Generate a query that returns a list of information to match the mask.
void WHO(std::deque<std::string> Command, User &User)
{
	(void)Command;
	(void)User;
	std::cout << "WHO" << std::endl;
}

//WHOIS [ <target> ] <mask>
//-> Query info about a particular user.
void WHOIS(std::deque<std::string> Command, User &User)
{
	(void)Command;
	(void)User;
	std::cout << "WHOIS" << std::endl;
}

//WHOWAS <nickname> [ <count> [ <target> ] ]
//-> Ask for info about a nickname that no longer exists. 
void WHOWAS(std::deque<std::string> Command, User &User)
{
	(void)Command;
	(void)User;
	std::cout << "WHOWAS" << std::endl;
}

/*User commands for channels:*/

/*Operator commands:*/

//KILL <nickname> <comment>
//-> Cause a client-server connection to be closed by the server.
void KILL(std::deque<std::string> Command, User &user)
{
	(void)Command;
	(void)user;
	std::cout << "KILL" << std::endl;
}

//DIE (optional)
//-> Shut down the server.
void DIE(std::deque<std::string> Command, User &user)
{
	(void)Command;
	(void)user;
	std::cout << "DIE" << std::endl;
}

//RESTART
//-> Force the server to restart itself.
void RESTART(std::deque<std::string> Command, User &user)
{
	(void)Command;
	(void)user;
	std::cout << "RESTART" << std::endl;
}