#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include <vector>
# include <string>
# include <iostream>
# include "utils.hpp"

class Server;
class User;
class Channel;

// typedef     void (*command)(User &user, Server &server);

/*Server commands*/

void PING(User &User, Server &server);
void PONG(User &User, Server &server);
void QUIT(User &User, Server &server);

/*User commands:*/

void PASS(User &User, Server &server);
void NICK(User &User, Server &server);
void USER(User &User, Server &server);
void OPER(User &User, Server &server);
void PRIVMSG(User &User, Server &server);
void QUIT(User &User, Server &server);
void PRIVMSG(User &User, Server &server);
void NOTICE(User &User, Server &server);
void MOTD(User &User, Server &server);
void WHOIS(User &User, Server &server);

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

void OPER(User &User, Server &server);
void KILL(User &user, Server &server);
void DIE(User &user, Server &server);


/*Command utils:*/

Channel*	findChannel(std::string &channelName, Server &server);
User*		findUser(std::string &userName, Server &server);
bool        isOperator(const std::string &username, Server &server);
void 		removeUserFromChannel(Channel *channel, User &user, Server &server);
void 		partFromAllChannels(User &user, Server &server);
std::string	createCommandMessage(Server &server);
void		channelWelcomeMessage(Channel &chan, User &user);

#endif
