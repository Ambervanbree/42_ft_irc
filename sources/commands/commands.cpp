#include "commands.hpp"

/*Server commands*/

// PASS <password> <version> <flags>
// set a connection pas
void PASS(std::deque<std::string> Command, User &User)
{
	(void)Command;
	(void)User;
	std::cout << "PASS" << std::endl;
}

// NICK <nickname> <hopcount> <username> <host> <servertoken> <umode> <realname>
// -> Combination of NICK (the user version), USER and MODE.
void NICK(std::deque<std::string> Command, User &User)
{
	(void)Command;
	(void)User;
	std::cout << "NICK" << std::endl;
}

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

//JOIN <channel>
//-> Check if a client is allowed to join a channel.
void JOIN(std::deque<std::string> Command, User &User)
{
	(void)Command;
	(void)User;
	std::cout << "JOIN" << std::endl;
}

/*User commands:*/

//PASS <password>
//-> Set a connection password.
/*void PASS(std::deque<std::string> Command, User &User)
{
	(void)Command;
	(void)User;
	std::cout << "PASS" << std::endl;
}*/

//NICK <nickname>
//-> Give user a nickname or change the existing one.
/*void NICK(std::deque<std::string> Command, User &User)
{
	(void)Command;
	(void)User;
	std::cout << "NICK" << std::endl;
}*/

//USER <user> <mode> <unused> <realname>
//-> Specify the username, hostname and realname of 
//   a new user at the beginning of connection
void USER(std::deque<std::string> Command, User &User)
{
	(void)Command;
	(void)User;
	std::cout << "USER" << std::endl;
}

//OPER <name> <password>
//-> Obtain operator priviliges.
void OPER(std::deque<std::string> Command, User &User)
{
	(void)Command;
	(void)User;
	std::cout << "OPER" << std::endl;
}

//MODE <nickname>
//-> Change status.
void MODE(std::deque<std::string> Command, User &User)
{
	(void)Command;
	(void)User;
	std::cout << "MODE" << std::endl;
}

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

//JOIN <channel>
//-> Start listening a specific channel.
/*void JOIN(std::deque<std::string> Command, User &User)
{
	(void)Command;
	(void)User;
	std::cout << "JOIN" << std::endl;
}*/

//PART <channel>
//-> User is removed from active members list.
void PART(std::deque<std::string> Command, User &User)
{
	(void)Command;
	(void)User;
	std::cout << "PART" << std::endl;
}

//MODE <channel>
//-> Change characteristics of a channel.
/*void MODE(std::deque<std::string> Command, User &User)
{
	(void)Command;
	(void)User;
	std::cout << "MODE" << std::endl;
}*/

//TOPIC <channel> [ <topic> ]
//-> Change or view the topic of a channel.
void TOPIC(std::deque<std::string> Command, User &User)
{
	(void)Command;
	(void)User;
	std::cout << "TOPIC" << std::endl;
}

//NAMES [ <channel> ]
//-> List all nicknames visible to the client. 
void NAMES(std::deque<std::string> Command, User &User)
{
	(void)Command;
	(void)User;
	std::cout << "NAMES" << std::endl;
}

//LIST [ <channel> ]
//-> List channels and their topics.
void LIST(std::deque<std::string> Command, User &user)
{
	(void)Command;
	(void)user;
	std::cout << "LIST" << std::endl;
}

//INVITE <nickname> <channel>
//-> Invite a user to a channel.
void INVITE(std::deque<std::string> Command, User &user)
{
	(void)Command;
	(void)user;
	std::cout << "INVITE" << std::endl;
}

//KICK <channel> <user> [<comment>]
//-> Request forced removal of a user from a channel.
void KICK(std::deque<std::string> Command, User &user)
{
	(void)Command;
	(void)user;
	std::cout << "KICK" << std::endl;
}

/*Operator commands:*/

//SQUIT <server> <comment>
//-> Disconnect server links.
/*void SQUIT(std::deque<std::string> Command, User &user)
{
	(void)Command;
	(void)user;
	std::cout << "SQUIT" << std::endl;
}*/

//CONNECT <target server> <port> [ <remote server> ]
//-> Connect to another server.
void CONNECT(std::deque<std::string> Command, User &user)
{
	(void)Command;
	(void)user;
	std::cout << "CONNECT" << std::endl;
}

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