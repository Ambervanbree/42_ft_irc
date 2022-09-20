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

void PASS(std::vector<std::string> Command, User &User);
void NICK(std::vector<std::string> Command, User &User);
void PING(std::vector<std::string> Command, User &User);
void PONG(std::vector<std::string> Command, User &User);
void ERROR(std::vector<std::string> Command, User &User);
void WALLOPS(std::vector<std::string> Command, User &User);
void QUIT(std::vector<std::string> Command, User &User);
void SQUIT(std::vector<std::string> Command, User &User);
void JOIN(std::vector<std::string> Command, User &User);

/*User commands:*/

void PASS(std::vector<std::string> Command, User &User);
void NICK(std::vector<std::string> Command, User &User);
void USER(std::vector<std::string> Command, User &User);
void OPER(std::vector<std::string> Command, User &User);
void MODE(std::vector<std::string> Command, User &User);
void SERVICE(std::vector<std::string> Command, User &User);
void QUIT(std::vector<std::string> Command, User &User);
void PRIVMSG(std::vector<std::string> Command, User &User);
void NOTICE(std::vector<std::string> Command, User &User);
void MOTD(std::vector<std::string> Command, User &User);
void LUSERS(std::vector<std::string> Command, User &User);
void VERSION(std::vector<std::string> Command, User &User);
void STATS(std::vector<std::string> Command, User &User);
void TIME(std::vector<std::string> Command, User &User);
void INFO(std::vector<std::string> Command, User &User);
void WHO(std::vector<std::string> Command, User &User);
void WHOIS(std::vector<std::string> Command, User &User);
void WHOWAS(std::vector<std::string> Command, User &User);

/*User commands for channels:*/

void JOIN(std::vector<std::string> Command, User &User);
void PART(std::vector<std::string> Command, User &User);
void MODE(std::vector<std::string> Command, User &User);
void TOPIC(std::vector<std::string> Command, User &User);
void NAMES(std::vector<std::string> Command, User &User);
void LIST(std::vector<std::string> Command, User &user);
void INVITE(std::vector<std::string> Command, User &user);
void KICK(std::vector<std::string> Command, User &user);

/*Operator commands:*/

void SQUIT(std::vector<std::string> Command, User &user);
void CONNECT(std::vector<std::string> Command, User &user);
void KILL(std::vector<std::string> Command, User &user);
void DIE(std::vector<std::string> Command, User &user);
void RESTART(std::vector<std::string> Command, User &user);

#endif
