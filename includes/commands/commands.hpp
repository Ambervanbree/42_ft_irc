#ifndef COMMANDS_HPP
# define COMMANDS_HPP
# include <vector>
# include <string>
# include <iostream>
# include "user.hpp"
# include "utils.hpp"

/*Placeholder to channel class*/
class Channel
{
	public:
		Channel() {};
		~Channel() {};
};

/*Server commands*/

void PASS(std::vector<std::string> Command, User &User, Channel &channel);
void NICK(std::vector<std::string> Command, User &User, Channel &channel);
void PING(std::vector<std::string> Command, User &User, Channel &channel);
void PONG(std::vector<std::string> Command, User &User, Channel &channel);
void ERROR(std::vector<std::string> Command, User &User, Channel &channel);
void WALLOPS(std::vector<std::string> Command, User &User, Channel &channel);
void QUIT(std::vector<std::string> Command, User &User, Channel &channel);
void SQUIT(std::vector<std::string> Command, User &User, Channel &channel);
void JOIN(std::vector<std::string> Command, User &User, Channel &channel);

/*User commands:*/

void PASS(std::vector<std::string> Command, User &User, Channel &channel);
void NICK(std::vector<std::string> Command, User &User, Channel &channel);
void USER(std::vector<std::string> Command, User &User, Channel &channel);
void OPER(std::vector<std::string> Command, User &User, Channel &channel);
void MODE(std::vector<std::string> Command, User &User, Channel &channel);
void SERVICE(std::vector<std::string> Command, User &User, Channel &channel);
void QUIT(std::vector<std::string> Command, User &User, Channel &channel);
void PRIVMSG(std::vector<std::string> Command, User &User, Channel &channel);
void NOTICE(std::vector<std::string> Command, User &User, Channel &channel);
void MOTD(std::vector<std::string> Command, User &User, Channel &channel);
void LUSERS(std::vector<std::string> Command, User &User, Channel &channel);
void VERSION(std::vector<std::string> Command, User &User, Channel &channel);
void STATS(std::vector<std::string> Command, User &User, Channel &channel);
void TIME(std::vector<std::string> Command, User &User, Channel &channel);
void INFO(std::vector<std::string> Command, User &User, Channel &channel);
void WHO(std::vector<std::string> Command, User &User, Channel &channel);
void WHOIS(std::vector<std::string> Command, User &User, Channel &channel);
void WHOWAS(std::vector<std::string> Command, User &User, Channel &channel);

/*User commands for channels:*/

void JOIN(std::vector<std::string> Command, User &User, Channel &channel);
void PART(std::vector<std::string> Command, User &User, Channel &channel);
void MODE(std::vector<std::string> Command, User &User, Channel &channel);
void TOPIC(std::vector<std::string> Command, User &User, Channel &channel);
void NAMES(std::vector<std::string> Command, User &User, Channel &channel);
void LIST(std::vector<std::string> Command, User &user, Channel &channel);
void INVITE(std::vector<std::string> Command, User &user, Channel &channel);
void KICK(std::vector<std::string> Command, User &user, Channel &channel);

/*Operator commands:*/

void SQUIT(std::vector<std::string> Command, User &user, Channel &channel);
void CONNECT(std::vector<std::string> Command, User &user, Channel &channel);
void KILL(std::vector<std::string> Command, User &user, Channel &channel);
void DIE(std::vector<std::string> Command, User &user, Channel &channel);
void RESTART(std::vector<std::string> Command, User &user, Channel &channel);

#endif
