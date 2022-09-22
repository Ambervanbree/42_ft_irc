#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include <deque>
# include <vector>
# include <string>
# include <iostream>
# include "channel.hpp"
# include "user.hpp"
# include "utils.hpp"

class Server;

typedef void (*command)(std::deque<std::string> command, User &user, Server &server);

/*Server commands*/

// void PASS(std::deque<std::string> Command, User &User, Server &server);
void NICK(std::deque<std::string> Command, User &User, Server &server);
// void PING(std::deque<std::string> Command, User &User, Server &server);
// void PONG(std::deque<std::string> Command, User &User, Server &server);
// void ERROR(std::deque<std::string> Command, User &User, Server &server);
// void WALLOPS(std::deque<std::string> Command, User &User, Server &server);
// void QUIT(std::deque<std::string> Command, User &User, Server &server);
// void SQUIT(std::deque<std::string> Command, User &User, Server &server);
// void JOIN(std::deque<std::string> Command, User &User, Server &server);

/*User commands:*/

// void PASS(std::deque<std::string> Command, User &User, Server &server);
// void USER(std::deque<std::string> Command, User &User, Server &server);
// void OPER(std::deque<std::string> Command, User &User, Server &server);
// void MODE(std::deque<std::string> Command, User &User, Server &server);
// void SERVICE(std::deque<std::string> Command, User &User, Server &server);
// void QUIT(std::deque<std::string> Command, User &User, Server &server);
// void PRIVMSG(std::deque<std::string> Command, User &User, Server &server);
// void NOTICE(std::deque<std::string> Command, User &User, Server &server);
// void MOTD(std::deque<std::string> Command, User &User, Server &server);
// void LUSERS(std::deque<std::string> Command, User &User, Server &server);
// void VERSION(std::deque<std::string> Command, User &User, Server &server);
// void STATS(std::deque<std::string> Command, User &User, Server &server);
// void TIME(std::deque<std::string> Command, User &User, Server &server);
// void INFO(std::deque<std::string> Command, User &User, Server &server);
// void WHO(std::deque<std::string> Command, User &User, Server &server);
// void WHOIS(std::deque<std::string> Command, User &User, Server &server);
// void WHOWAS(std::deque<std::string> Command, User &User, Server &server);

/*User commands for channels:*/

void JOIN(std::deque<std::string> command, User &user, Server &server);
// void PART(std::deque<std::string> Command, User &User);
void MODE(std::deque<std::string> command, User &user, Server &server);
// void TOPIC(std::deque<std::string> Command, User &User);
// void NAMES(std::deque<std::string> Command, User &User);
// void LIST(std::deque<std::string> Command, User &user);
// void INVITE(std::deque<std::string> Command, User &user);
// void KICK(std::deque<std::string> Command, User &user);

/*Operator commands:*/

// void SQUIT(std::deque<std::string> Command, User &user);
// void CONNECT(std::deque<std::string> Command, User &user);
// void KILL(std::deque<std::string> Command, User &user);
// void DIE(std::deque<std::string> Command, User &user);
// void RESTART(std::deque<std::string> Command, User &user);


/*Command utils:*/
Channel*	findChannel(std::string &channelName, Server &server);

#endif
