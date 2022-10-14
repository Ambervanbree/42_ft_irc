#include "channel.hpp"
#include "user.hpp"
#include "server.hpp"
#include "commands.hpp"
#include <fstream>

void	sendMOTD(Server &server, User &user){
	std::ifstream	MOTDfile;
	std::string		line;
	std::string		MOTDbuffer;

	(void)server;
	(void)user;
	MOTDfile.open("other/motd.txt");
	if (MOTDfile.is_open()){
		std::cout << "RPL_MOTDSTART (375)" << std::endl;
		while (MOTDfile.good()){
			std::getline(MOTDfile, line);
			// RPL to user with line as a comment:
			std::cout << "RPL_MOTD (372)" << std::endl;
		}
		std::cout << "RPL_ENDOFMOTD (376)" << std::endl;
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
	sendMOTD(server, user);
}