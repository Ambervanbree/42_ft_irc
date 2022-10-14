#ifndef REPLIES_HPP
# define REPLIES_HPP
# include <string>

/* Registration RPL */

# define RPL_WELCOME(nick)                  "001 " + nick + " :Welcome to the Internet Relay Network, " + nick + "\r\n"

/* RPL */

# define RPL_UMODEIS(nick, mode)			    "221 " + nick + " " + mode + "\r\n"
// define RPL_LISTSTART(nick)                   "321 " + nick + " Channel :Users Name\r\n" 
# define RPL_LIST(nick, channel, topic) 		"322 " + nick + " " + channel + " :" + topic + "\r\n"
# define RPL_LISTEND(nick)					    "323 " + nick + " :End of /LIST\r\n"
# define RPL_CHANNELMODEIS(nick, chan, modestr) "324 " + nick + " " + chan + " " + modestr + "\r\n"
# define RPL_NOTOPIC(nick, channel)			    "331 " + nick + " " + channel + " :No topic is set\r\n"
# define RPL_TOPIC(nick, channel, topic)	    "332 " + nick + " " + channel + " :" + topic + "\r\n"
# define RPL_TOPICWHOTIME(nick, channel, user, setat)   "333 " + nick + " " + channel + " " + user + " " + setat + "\r\n"
# define RPL_INVITING(channel, invitee)         "341 " + channel + " " + invitee + "\r\n"
# define RPL_NAMREPLY(nick, channel, users)		"353 " + nick + " = " + channel + " :" + users + "\r\n"
# define RPL_ENDOFNAMES(nick, channel)          "366 " + nick + " " + channel +  " :End of /NAMES list\r\n"
# define RPL_BANLIST(nick, channel, masks)		"367 " + nick + " " + channel + " " + masks + "\r\n"
# define RPL_ENDOFBANLIST(nick, channel)		"368 " + nick + " " + channel + " :End of channel ban list\r\n"
//# define RPL_MOTD(nick, comment) 			    "372 " + nick + " :" + comment + "\r\n"
# define RPL_MOTDSTART(nick)					"375 " + nick + " :- IRC Message of the day - \r\n"
# define RPL_ENDOFMOTD(nick)					"376 " + nick + " :End of /MOTD command\r\n"
//# define RPL_YOUREOPER(nick)				    "381 " + nick + " :You are now an IRC operator\r\n"

/* ERR */

# define ERR_NOSUCHNICK(nick)     	            "401 " + nick + " :No such nick/channel\r\n"
# define ERR_NOSUCHSERVER(server)          		"402 " + server + " :No such server\r\n"   
# define ERR_NOSUCHCHANNEL(channel)				"403 " + channel + " :No such channel\r\n"
# define ERR_CANNOTSENDTOCHAN(nick, channel)	"404 " + nick + " " + channel + " :Cannot send to channel\r\n"
# define ERR_TOOMANYCHANNELS(channel)			"405 " + channel + " :You have joined too many channels\r\n"
# define ERR_TOOMANYTARGETS						"407 :Too many targets specified"
// # define ERR_NOORIGIN                        "409 * :No origin specified\r\n"
# define ERR_NORECIPIENT						"411 :No recipient specified\r\n"
# define ERR_NOTEXTTOSEND						"412 :No text to send"
# define ERR_UNKNOWNCOMMAND                     "421 * :Command not found\r\n"
# define ERR_NOMOTD								"422 :MOTD File is missing"
# define ERR_NONICKNAMEGIVEN					"431 :No nickname given\r\n"
# define ERR_ERRONEUSNICKNAME(nick)				"432 " + nick + " :Erroneous nickname\r\n"
# define ERR_NICKNAMEINUSE(nick)				"433 " + nick + " :Nickname is already in user\r\n"
# define ERR_USERNOTINCHANNEL(nick, channel)	"441 " + nick + " " + channel + " :They aren't on that channel\r\n"
# define ERR_NOTONCHANNEL(nick, channel)		"442 " + nick + " " + channel + " :You're not on that channel\r\n"
# define ERR_USERONCHANNEL(nick, channel)		"443 " + nick + " " + channel + " :is already on channel\r\n"
// # define ERR_NOTREGISTERED                    "451 * :You have not registered\r\n"
# define ERR_NEEDMOREPARAMS(nick, cmd_name)		"461 " + nick + " " + cmd_name + " :Not enough parameters\r\n"
# define ERR_ALREADYTREGISTERED(nick)			"462 " + nick + " :Unauthorized command (already registered)\r\n"
# define ERR_PASSWDMISMATCH						"464 :Password incorrect\r\n"
# define ERR_UNKNOWNMODE(nick, flag)			"472 " + nick + " " + flag + " :is unknown mode char to me\r\n"
# define ERR_BANNEDFROMCHAN(channel)			"474 " + channel + " :Cannot join channel (+b)\r\n"
# define ERR_BADCHANNELKEY(channel)				"475 " + channel + " :Cannot join channel (+k)\r\n"
# define ERR_BADCHANMASK(channel)				"476 " + channel + " :Bad Channel Mask\r\n"
# define ERR_NOPRIVILEGES(nick)                 "481 " + nick + " :Permission Denied- You're not an IRC operator\r\n"
# define ERR_CHANPRIVSNEEDED(nick, channel)		"482 " + nick + " " + channel + " :You're not channel operator\r\n"
# define ERR_NOOPERHOST(nick)					"491 " + nick + " :No O-lines for your host\r\n"
# define ERR_UMODEUNKNOWMFLAG(nick, channel)	"501 " + nick + " " + channel + " :Unknown :MODE flag\r\n"
// # define ERR_USERSDONTMATCH(nick)            "502 :" + nick + " :Cant change mode for other users\r\n"

/* Command messages */

# define JOIN_message(chan)								" JOIN " + chan + "\r\n"
# define PART_message(chan)								" PART " + chan + "\r\n"
# define PART_message_2(chan, message)					" PART " + chan + " :" + message + "\r\n"
# define MODE_message(chan, args)						" MODE " + args + "\r\n"
# define TOPIC_message(chan, topic)						" TOPIC " + chan + " :" + topic + "\r\n"
# define INVITE_message(inviter, chan, invitee)			":" + inviter + " INVITE " + invitee + " " + chan + "\r\n"
# define KICK_message(chan, kicked)						" KICK " + kicked + "\r\n"
# define KICK_message_2(chan, kicked, reason)			" KICK " + kicked + " :" + reason + "\r\n"
# define PRIVMSG_message(nick, recipient, message)		":" + nick + " PRIVMSG " + recipient + " " + message + "\r\n"
# define PRIVMSG_message_c(recipient, message)			" PRIVMSG " + recipient + " " + message + "\r\n"
# define NOTICE_message(nick, recipient, message)		":" + nick + " NOTICE " + recipient + " " + message + "\r\n"
# define NOTICE_message_c(recipient, message)			" NOTICE " + recipient + " " + message + "\r\n"

#endif