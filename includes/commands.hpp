#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include <deque>
# include <vector>
# include <string>
# include <iostream>
// # include "channel.hpp"
// # include "user.hpp"
# include "utils.hpp"

class Server;
class User;
class Channel;

// typedef     void (*command)(User &user, Server &server);

/*Server commands*/

// void PING(User &User, Server &server);
// void PONG(User &User, Server &server);
// void ERROR(User &User, Server &server);
// void WALLOPS(User &User, Server &server);
// void QUIT(User &User, Server &server);
// void SQUIT(User &User, Server &server);
// void JOIN(User &User, Server &server);

/*User commands:*/

void PASS(User &User, Server &server);
void NICK(User &User, Server &server);
void USER(User &User, Server &server);
// void OPER(User &User, Server &server);
// void MODE(User &User, Server &server);
// void SERVICE(User &User, Server &server);
// void QUIT(User &User, Server &server);
// void PRIVMSG(User &User, Server &server);
// void NOTICE(User &User, Server &server);
// void MOTD(User &User, Server &server);
// void LUSERS(User &User, Server &server);
// void VERSION(User &User, Server &server);
// void STATS(User &User, Server &server);
// void TIME(User &User, Server &server);
// void INFO(User &User, Server &server);
// void WHO(User &User, Server &server);
// void WHOIS(User &User, Server &server);
// void WHOWAS(User &User, Server &server);

/*User commands for channels:*/

void JOIN(User &user, Server &server);
void MODE(User &user, Server &server);
void PART(User &user, Server &server);
void TOPIC(User &user, Server &server);
void NAMES(User &user, Server &server);
void LIST(User &user, Server &server);
void INVITE(User &user, Server &server);
void KICK(User &user, Server &server);

/*Operator commands:*/

// void SQUIT(User &user);
// void CONNECT(User &user);
// void KILL(User &user);
// void DIE(User &user);
// void RESTART(User &user);


/*Command utils:*/
Channel*	findChannel(std::string &channelName, Server &server);
User*		findUser(std::string &userName, Server &server);
void 		removeUserFromChannel(Channel *channel, User &user, Server &server);

#endif
