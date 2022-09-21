#ifndef PARSER_HPP
# define PARSER_HPP
# include <map>
# include <string>
# include <iostream>
# include <vector>
# include "commands.hpp"

typedef void (*command)(std::deque<std::string> command, User &user);


/*Things to add to the server*/
class Parser
{
	private: 
		void _setCommands();
		
		std::deque<std::string> _splitMessage(std::string message);
		void _launchCommand(std::deque<std::string> commande, User &user);

		std::map<std::string, command> _commands;

		Parser(const Parser &other);
		Parser &operator=(const Parser &other);
	public:
		Parser();
		~Parser();
		void interpretCommand(std::string message, User &user);
};

#endif