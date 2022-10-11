#include "channel.hpp"
#include "user.hpp"
#include "server.hpp"
#include "commands.hpp"
#include <fstream>

# define RESET   "\033[0m"
# define GREEN	 "\033[32m"
# define YELLOW  "\033[33m"
# define BLUE    "\033[34m"
# define CYAN    "\033[36m"
# define RED     "\033[31m"
# define MAGENTA "\033[35m"
# define BOLD    "\e[1m"
# define ITALIC	 "\e[3m"

void	sendMOTD(User &user){
	std::ifstream	MOTDfile;
	std::string		line;

	MOTDfile.open("other/motd.txt");
	if (MOTDfile.is_open()){
		while (MOTDfile.good()){
			std::getline(MOTDfile, line);
			std::cout << line << std::endl;
			//PRIVMSG to user: line + "\n";
		}
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