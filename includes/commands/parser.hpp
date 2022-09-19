#ifndef PARSER_HPP
# define PARSER_HPP
# include <map>
# include <string>
# include <iostream>
# include <vector>
# include "commands.hpp"

typedef void (*command)(std::vector<std::string> command, User user, Channel channel);


/*Things to add to the server*/

/*private*/
void _setCommands();
void _setReply();
std::vector<std::string> _splitMessage(std::string message);
void _launchCommand(std::vector<std::string> commande, User user, Channel channel);

std::map<std::string, command>  _commands;

/*public*/
void interpretCommand(std::string message, User user, Channel channel);

#endif