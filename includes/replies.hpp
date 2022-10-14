#ifndef REPLIES_HPP
# define REPLIES_HPP
# include <string>

/* Registration RPL */

# define RPL_WELCOME(nick)                  "001 " + nick + " :Welcome to the Internet Relay Network, " + nick + "\r\n"

/* RPL */

# define RPL_UMODEIS(nick, mode)			    "221 " + nick + " " + mode + "\r\n"
// define RPL_LISTSTART(nick)                   "321 " + nick + " Channel :Users Name\r\n" 
# define RPL_LIST(nick, channel, nbuser, topic) "322 " + nick + " " + channel + " " + nbuser + " :" + topic + "\r\n"
# define RPL_LISTEND(nick)					    "323 " + nick + " :End of /LIST\r\n"
# define RPL_CHANNELMODEIS(nick, chan, modestr, modeargs)    "324 " + nick + " " + chan + " " + modestr + " " + modeargs + "...\r\n"
# define RPL_NOTOPIC(nick, channel)			    "331 " + nick + " " + channel + " :No topic is set\r\n"
# define RPL_TOPIC(nick, channel, topic)	    "332 " + nick + " " + channel + " :" + topic + "\r\n"
# define RPL_TOPICWHOTIME(nick, channel, user, setat)   "333 " + nick + " " + channel + " " + user + " " + setat + "\r\n"
# define RPL_INVITING(channel, invitee)         "341 " + channel + " " + invitee + "\r\n"
# define RPL_NAMREPLY(nick, channel, users)		"353 " + nick + " = " + channel + " :" + users + "\r\n"
# define RPL_ENDOFNAMES(nick, channel)          "366 " + nick + " " + channel +  " :End of /NAMES list\r\n"
# define RPL_BANLIST(nick, channel, mask)		"367 " + nick + " " + channel + " " + mask + "\r\n"
# define RPL_ENDOFBANLIST(nick, channel)		"368 " + nick + " " + channel + " :End of channel ban list\r\n"
//# define RPL_MOTD(nick, comment) 			    "372 " + nick + " :" + comment + "\r\n"
//# define RPL_MOTDSTART(nick)					"375 " + nick + " :- IRC Message of the day - \r\n"
//# define RPL_ENDOFMOTD(nick)					"376 " + nick + " :End of /MOTD command\r\n"
//# define RPL_YOUREOPER(nick)				    "381 " + nick + " :You are now an IRC operator\r\n"

/* ERR */

// # define ERR_NOSUCHNICK(nick)                "401 " + nick + " :No such nick/channel\r\n"
// # define ERR_NOSUCHSERVER(server)            "402 " + server + " :No such server\r\n"   
# define ERR_NOSUCHCHANNEL(channel)				"403 " + channel + " :No such channel\r\n"
// # define ERR_CANNOTSENDTOCHAN(nick, channel) "404 " + nick + " " + channel + " :Cannot send to channel\r\n"
# define ERR_TOOMANYCHANNELS(channel)			"405 " + channel + " :You have joined too many channels\r\n"
// # define ERR_NOORIGIN                        "409 * :No origin specified\r\n"
# define ERR_UNKNOWNCOMMAND                     "421 * :Command not found\r\n"
# define ERR_NONICKNAMEGIVEN					"431 :No nickname given\r\n"
# define ERR_ERRONEUSNICKNAME(nick)				"432 " + nick + " :Erroneous nickname\r\n"
# define ERR_NICKNAMEINUSE(nick)				"433 " + nick + " :Nickname is already in user\r\n"
# define ERR_USERNOTINCHANNEL(nick, channel)	"441 " + nick + " " + channel + " :They aren't on that channel\r\n"
# define ERR_NOTONCHANNEL(nick, channel)		"442 " + nick + " " + channel + " :You're not on that channel\r\n"
# define ERR_USERONCHANNEL(user, channel)		"443 " + user + " " + channel + " :is already on channel\r\n"
// # define ERR_NOTREGISTERED                    "451 * :You have not registered\r\n"
# define ERR_NEEDMOREPARAMS(nick, cmd_name)		"461 " + nick + " " + cmd_name + " :Not enough parameters\r\n"
# define ERR_ALREADYTREGISTERED(nick)			"462 " + nick + " :Unauthorized command (already registered)\r\n"
# define ERR_PASSWDMISMATCH						"464 :Password incorrect\r\n"
# define ERR_UNKNOWNMODE(nick, flag, channel)	"472 " + nick + " " + flag + " :isunknown node char to me for " + channel + "\r\n"
# define ERR_BANNEDFROMCHAN(channel)			"474 " + channel + " :Cannot join channel (+b)\r\n"
# define ERR_BADCHANNELKEY(channel)				"475 " + channel + " :Cannot join channel (+k)\r\n"
# define ERR_BADCHANMASK(channel)				"476 " + channel + " :Bad Channel Mask\r\n"
// # define ERR_NOPRIVILEGES(nick)              "481 " + nick + " :Permission Denied- You're not an IRC operator\r\n"
# define ERR_CHANPRIVSNEEDED(nick, channel)		"482 " + nick + " " + channel + " :You're not channel operator\r\n"
# define ERR_NOOPERHOST(nick)					"491 " + nick + " :No O-lines for your host\r\n"
# define ERR_UMODEUNKNOWMFLAG(nick, channel)	"501 " + nick + " " + channel + " :Unknown :MODE flag\r\n"
// # define ERR_USERSDONTMATCH(nick)            "502 :" + nick + " :Cant change mode for other users\r\n"

/* Command messages */

// # define JOIN_message(nick, chan)					":" + nick + " JOIN " + chan " "\r\n"
// # define PART_message(nick, chan)					":" + nick + " PART " + chan + "\r\n"
// # define PART_message(nick, chan, message)			":" + nick + " PART " + chan + " :" + message + "\r\n"
// # define MODE_message(nick, chan, args)				":" + nick + " MODE " + args + "\r\n"
// # define TOPIC_message(nick, chan, topic)			":" + nick + " TOPIC " + " :" + topic + "\r\n"
// # define INVITE_message(inviter, chan, invitee)		":" + inviter + " INVITE " + invitee + " " + chan + "\r\n"
// # define KICK_message(kicker, chan, kicked)			":" + kicker + " KICK " + kicked + "\r\n"
// # define KICK_message(kicker, chan, kicked, reason)	":" + kicker + " KICK " + kicked + " :" + reason + "\r\n"
// # define PRIVMSG_message(sender, reciever, message)	":" + sender + " PRIVMSG " + receiver + " :" + message + "\r\n"
// # define NOTICE_message(sender, reciever, message)	":" + sender + " NOTICE " + receiver + " :" + message + "\r\n"

#endif