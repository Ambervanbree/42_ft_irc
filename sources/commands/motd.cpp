#include "channel.hpp"
#include "user.hpp"
#include "server.hpp"
#include "commands.hpp"
#include <fstream>

void	sendMOTD(User &user){
	std::ifstream	MOTDfile;
	std::string		line;
	std::string		MOTDbuffer;

	MOTDfile.open("other/motd.txt");
	if (MOTDfile.is_open()){
		user.addRepliesToBuffer(RPL_MOTDSTART(user.getNickname()));
		while (MOTDfile.good()){
			std::getline(MOTDfile, line);
			line += "\r\n";
			user.addRepliesToBuffer(line);
			// std::cout << "RPL_MOTD (372)" << std::endl; --> this is too long (TODO - to discuss)
		}
		user.addRepliesToBuffer(RPL_ENDOFMOTD(user.getNickname()));
		MOTDfile.close();
	}
	else
		user.addRepliesToBuffer(ERR_NOMOTD);
}

void MOTD(User &user, Server &server){
	if (!user.isRegistered())
		return ;
	if (!server.getArgs().empty()){
		if (!(server.getArgs()[0] == "localhost" || server.getArgs()[0] == "127.0.0.1")) // TODO -> not sure if this is correct
			user.addRepliesToBuffer(ERR_NOSUCHSERVER(server.getArgs()[0]));
	}
	sendMOTD(user);
}