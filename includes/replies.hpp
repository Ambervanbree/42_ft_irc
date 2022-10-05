#ifndef REPLIES_HPP
# define REPLIES_HPP

/* Registration RPL */

# define RPL_WELCOME(nick, nickmask)        "001 " + nick + " :Welcome to the ICC Network, " + nickmask;

/* RPL */

# define RPL_UMODEIS						"221";
# define RPL_LIST							"322";
# define RPL_LISTEND						"323";
# define RPL_CHANNELMODEIS					"324";
# define RPL_NOTOPIC						"331";
# define RPL_TOPIC							"332";
# define RPL_TOPICWHOTIME					"333";
# define RPL_NAMREPLY						"353";
# define RPL_ENDOFNAMES						"366";
# define RPL_BANLIST						"367";
# define RPL_ENDOFBANLIST					"368";
# define RPL_YOUREOPER						"381";


/* ERR */

# define ERR_NOSUCHCHANNEL(channel)				"403 " + channel + " :No such channel";
# define ERR_TOOMANYCHANNELS(channel)			"405 " + channel + " :You have joined too many channels";
# define ERR_NONICKNAMEGIVEN					"431 " + " :No nickname given";
# define ERR_ERRONEUSNICKNAME(nick)				"432 " + nick + " :Erroneous nickname";
# define ERR_NICKNAMEINUSE(nick)				"433 " + nick + " :Nickname is already in use";
# define ERR_USERNOTINCHANNEL(nick, channel)	"441 " + nick + " " + channel + " :They aren't on that channel";
# define ERR_NOTONCHANNEL(channel)				"442 " + channel + " :You're not on that channel";
# define ERR_USERONCHANNEL(user, channel)		"443 " + user + " " + channel + " :is already on channel";
# define ERR_NEEDMOREPARAMS(cmd_name)			"461 " + command + " :Not enough parameters";
# define ERR_ALREADTREGISTERED					"462 :Unauthorized command (already registered";
# define ERR_PASSWDMISMATCH						"464 :Password incorrect";
# define ERR_UNKNOWNMODE(char, channel)			"472 " + char + " :isunknown node char to me for " + channel;
# define ERR_BANNEDFROMCHAN						"474 ";
# define ERR_BADCHANNELKEY						"475 ";
# define ERR_BADCHANMASK(channel)				"476 " + channel + " :Bad Channel Mask";
# define ERR_CHANPRIVSNEEDED(channel)			"482 " + channel + " :You're not channel operator";
# define ERR_NOOPERHOST							"491 :No O-lines for your host";
# define ERR_UMODEUNKNOWMFLAG					"501 :Unknown :MODE flag";

#endif 