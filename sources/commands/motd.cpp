#include "channel.hpp"
#include "user.hpp"
#include "server.hpp"
#include "commands.hpp"
#include <fstream>

void	sendMOTD(User &user){
	std::ifstream	MOTDfile;
	std::string		line;

	MOTDfile.open("other/motd.txt");
	if (MOTDfile.is_open()){
		// PRIVMSG to user: RPL_MOTDSTART (375)
		while (MOTDfile.good()){
			std::getline(MOTDfile, line);
			std::cout << line << std::endl;
			//PRIVMSG to user: line + "\n";
		}
		// PRIVMSG to user: RPL_ENDOFMOTD (376)
		MOTDfile.close();
	}
	else
		std::cerr << "ERR_NOMOTD (422)" << std::endl;
}

void MOTD(User &user, Server &server){
// 	if (!user.isRegistered())
// 		return ;
	if (!server.getArgs().empty()){
		if (!(server.getArgs()[0] == "localhost" || server.getArgs()[0] == "127.0.0.1")){
			std::cerr << "ERR_NOSUCHSERVER (402)" << std::endl;
			return ;
		}
	}
	sendMOTD(user);
}