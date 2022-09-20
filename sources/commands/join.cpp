#include "channel.hpp"
#include "parser.hpp"

//JOIN <channel>
//-> Check if a client is allowed to join a channel.
void JOIN(std::vector<std::string>& Command, User& User)
{
	std::vector<std::string>::iterator 	it = Command.begin();
	for (; it != Command.end())
		std::cout << *it << std::endl;
	
	(void)User;
	(void)channel; 
	std::cout << "JOIN" << std::endl;
}
