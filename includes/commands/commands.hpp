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

// void PASS(std::deque<std::string> Command, User &User);
// void NICK(std::deque<std::string> Command, User &User);
// void PING(std::deque<std::string> Command, User &User);
// void PONG(std::deque<std::string> Command, User &User);
// void ERROR(std::deque<std::string> Command, User &User);
// void WALLOPS(std::deque<std::string> Command, User &User);
// void QUIT(std::deque<std::string> Command, User &User);
// void SQUIT(std::deque<std::string> Command, User &User);
// void JOIN(std::deque<std::string> Command, User &User);

/*User commands:*/

// void PASS(std::deque<std::string> Command, User &User);
// void NICK(std::deque<std::string> Command, User &User);
// void USER(std::deque<std::string> Command, User &User);
// void OPER(std::deque<std::string> Command, User &User);
// void MODE(std::deque<std::string> Command, User &User);
// void SERVICE(std::deque<std::string> Command, User &User);
// void QUIT(std::deque<std::string> Command, User &User);
// void PRIVMSG(std::deque<std::string> Command, User &User);
// void NOTICE(std::deque<std::string> Command, User &User);
// void MOTD(std::deque<std::string> Command, User &User);
// void LUSERS(std::deque<std::string> Command, User &User);
// void VERSION(std::deque<std::string> Command, User &User);
// void STATS(std::deque<std::string> Command, User &User);
// void TIME(std::deque<std::string> Command, User &User);
// void INFO(std::deque<std::string> Command, User &User);
// void WHO(std::deque<std::string> Command, User &User);
// void WHOIS(std::deque<std::string> Command, User &User);
// void WHOWAS(std::deque<std::string> Command, User &User);

/*User commands for channels:*/

void JOIN(std::deque<std::string> Command, User &User, Server &server);
// void PART(std::deque<std::string> Command, User &User);
// void MODE(std::deque<std::string> Command, User &User);
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


#endif
