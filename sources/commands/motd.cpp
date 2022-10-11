#include "channel.hpp"
#include "user.hpp"
#include "server.hpp"
#include "commands.hpp"

# define RESET   "\033[0m"
# define GREEN	 "\033[32m"
# define YELLOW  "\033[33m"
# define BLUE    "\033[34m"
# define CYAN    "\033[36m"
# define RED     "\033[31m"
# define MAGENTA "\033[35m"
# define BOLD    "\e[1m"
# define ITALIC	 "\e[3m"

void	createMOTD(std::string &message){
	message.append(CYAN).append(BOLD);
	message.append("Welcome to the ACC Power IRC Network\n\n");
	message.append("Server Information:\n");
	message.append(RESET);
	message.append("Server Hostname: 	localhost\n");
	message.append("Default port:		6667\n");
	message.append("Contact:		doesntexist@gmail.com\n\n");
	message.append(BOLD).append(CYAN);
	message.append("Some Inspiration:\n");
	message.append(RESET).append(ITALIC);
	message.append("Learn as if you will live forever, live like you will die tomorrow.\n");
	message.append(RESET);
	message.append("- Mahatma Ghandi\n");
	message.append(RESET);
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
	std::string message;
	createMOTD(message);
	(void)user;
	std::cout << message << std::endl;
}