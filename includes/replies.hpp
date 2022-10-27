#ifndef REPLIES_HPP
# define REPLIES_HPP
# include <string>

/* Registration RPL */

# define RPL_WELCOME(nick, nickmask)			"001 " + nick + " :Welcome to the Internet Relay Network, " + nickmask + "\r\n"
# define RPL_YOURHOST(nick)						"002 " + nick + " :Your host is ACC Power, running version 1.0.\r\n"
# define RPL_CREATED(nick, time)				"003 " + nick + " :This server was created " + time +  "\r\n"
# define RPL_MYINFO(nick)						"004 " + nick + " :ACC-Power 1.0 io kbto.\r\n"

/* RPL */


# define RPL_UMODEIS(nick, mode)	            "221 " + nick + " " + mode + "\r\n"
# define RPL_WHOISUSER(user, nick, name, realname)	"311 " + user + " " + nick + " " + name + " localhost * :" + realname + "\r\n"
# define RPL_WHOISSERVER(user, nick, server, info)	"312 " + user + " " + nick + " " + server + " :" + info "\r\n"
# define RPL_WHOISOPERATOR(user, nick)				"313 " + user + " " + nick + " :is an IRC operator\r\n"
# define RPL_WHOISIDLE(user, nick, idle)		"317 " + user + " " + nick + " " + idle + " :seconds idle\r\n"
# define RPL_ENDOFWHOIS(user, nick)				"318 " + user + " " + nick + " :End of /WHOIS list\r\n"
# define RPL_LIST(nick, channel, nbuser, topic)	"322 " + nick + " " + channel + " " + nbuser + " :" + topic + "\r\n"
# define RPL_LISTEND(nick)	       				"323 " + nick + " :End of /LIST\r\n"
# define RPL_CHANNELMODEIS(nick, chan, modestr) "324 " + nick + " " + chan + " " + modestr + "\r\n"
# define RPL_NOTOPIC(prefix, channel)			prefix + " 331 " + channel + " :No topic is set\r\n"
# define RPL_TOPIC(prefix, channel, topic)      prefix + " 332 " + channel + " :" + topic + "\r\n"
# define RPL_INVITING(nick, channel, invitee)   "341 " + nick + " " + invitee + " " + channel + " :Inviting " + invitee + " to " + channel + "\r\n"
# define RPL_NAMREPLY(prefix, nick, channel, users)   prefix + " 353 " + nick + " = " + channel + " :" + users + "\r\n"
# define RPL_ENDOFNAMES(prefix, nick, channel)  prefix + " 366 " + nick + " " + channel +  " :End of /NAMES list\r\n"
# define RPL_BANLIST(channel, masks)		    "367 " + channel + " " + masks + "\r\n"
# define RPL_ENDOFBANLIST(channel)		        "368 " + channel + " :End of channel ban list\r\n"
# define RPL_MOTD(nick, comment) 			    "372 " + nick + " :" + comment + "\r\n"
# define RPL_MOTDSTART(nick)					"375 " + nick + " :- Welcome stranger - \r\n"
# define RPL_ENDOFMOTD(nick)					"376 " + nick + " :End of /MOTD command\r\n"
# define RPL_YOUREOPER(nick)				    "381 " + nick + " :You are now an IRC operator\r\n"

/* ERR */

# define ERR_NOSUCHNICK(nick)     	            "401 " + nick + " :No such nick/channel\r\n"
# define ERR_NOSUCHSERVER(server)          		"402 " + server + " :No such server\r\n"   
# define ERR_NOSUCHCHANNEL(nick, channel)	    "403 " + nick + " " + channel + " :No such channel\r\n"
# define ERR_CANNOTSENDTOCHAN(nick, channel)	"404 " + nick + " " + channel + " :Cannot send to channel\r\n"
# define ERR_TOOMANYCHANNELS(channel)			"405 " + channel + " :You have joined too many channels\r\n"
# define ERR_TOOMANYTARGETS						"407 :Too many targets specified\r\n"
# define ERR_NOORIGIN                           "409 :No origin specified\r\n"
# define ERR_NORECIPIENT						"411 :No recipient specified\r\n"
# define ERR_NOTEXTTOSEND(nick)					"412 " + nick + " :No text to send\r\n"
# define ERR_UNKNOWNCOMMAND(cmd_name)           "421 " + cmd_name + " :Command not found: " + cmd_name + "\r\n"
# define ERR_NOMOTD								"422 :MOTD File is missing\r\n"
# define ERR_NONICKNAMEGIVEN(nick)				"431 " + nick + " :No nickname given\r\n"
# define ERR_ERRONEUSNICKNAME(nick)				"432 " + nick + " :Erroneous nickname\r\n"
# define ERR_NICKNAMEINUSE(nick, new_nick)		"433 " + nick + " " + new_nick + " :Nickname is already in use\r\n"
# define ERR_USERNOTINCHANNEL(nick, channel)	"441 " + nick + " " + channel + " :They aren't on that channel\r\n"
# define ERR_NOTONCHANNEL(nick, channel)	    "442 " + nick + " " + channel + " :You're not on that channel\r\n"
# define ERR_USERONCHANNEL(nick, channel)		"443 " + channel + " " + nick + " :is already on channel\r\n"
# define ERR_NEEDMOREPARAMS(nick, cmd_name)		"461 " + nick + " " + cmd_name + " :Not enough parameters\r\n"
# define ERR_ALREADYREGISTERED(nick)	        "462 " + nick + " :Unauthorized command (already registered)\r\n"
# define ERR_PASSWDMISMATCH(nick)				"464 " + nick + " :Password incorrect\r\n"
# define ERR_UNKNOWNMODE(flag)			        "472 " + flag + " :is unknown mode char to me\r\n"
# define ERR_BANNEDFROMCHAN(channel)		    "474 " + channel + " :Cannot join channel (+b)\r\n"
# define ERR_BADCHANNELKEY(channel)				"475 " + channel + " :Cannot join channel (+k)\r\n"
# define ERR_BADCHANMASK(channel)				"476 " + channel + " :Bad Channel Mask\r\n"
# define ERR_NOPRIVILEGES(nick)                 "481 " + nick + " :Permission Denied- You're not an IRC operator\r\n"
# define ERR_CHANPRIVSNEEDED(nick, channel)	    "482 " + nick + " " + channel + " :You're not channel operator\r\n"
# define ERR_NOOPERHOST(nick)     				"491 " + nick + " :No O-lines for your host\r\n"
# define ERR_NOORIGIN                           "409 :No origin specified\r\n"
# define ERR_UMODEUNKNOWMFLAG(nick)             "501 " + nick + " :Unknown MODE flag\r\n"
# define ERR_USERSDONTMATCH(nick)				"502 " + nick + " :Cannot change mode for other users\r\n"

/* Command messages */

# define JOIN_message(chan)					   			" JOIN " + chan + "\r\n"
# define PART_message(chan)								" PART " + chan + " :has left the channel\r\n"
# define PART_message_2(chan, message)					" PART " + chan + " " + message + "\r\n"
# define MODE_message(nick, args)						nick + " MODE " + args + "\r\n"
# define MODE_message_2(nick, chan, args)				nick + " MODE " + chan + " " + args + "\r\n"
# define TOPIC_message(chan, topic)						" TOPIC " + chan + " :" + topic   + "\r\n"
# define INVITE_message(inviter, chan, invitee)			":" + inviter + " INVITE " + invitee + " " + chan + "\r\n"
# define KICK_message(kicked, chan)						" KICK " + chan + " " + kicked + "\r\n"
# define KICK_message_2(kicked, chan, reason)			" KICK " + chan + " " + kicked + " " + reason + "\r\n"
# define PRIVMSG_message(nick, recipient, message)		":" + nick + " PRIVMSG " + recipient + " " + message + "\r\n"
# define PRIVMSG_message_c(recipient, message)			" PRIVMSG " + recipient + " " + message + "\r\n"
# define NOTICE_message(nick, recipient, message)		":" + nick + " NOTICE " + recipient + " " + message + "\r\n"
# define NOTICE_message_c(recipient, message)			" NOTICE " + recipient + " " + message + "\r\n"
# define ERROR_message(reason)                          " ERROR :Closing Link: " + reason + "\r\n"
# define QUIT_message(leaver, reason)                   ":" + leaver + " QUIT :" + reason + "\r\n"
# define PONG_message(host)                             "PONG " + host + "\r\n"
# define PING_message(host)                             "PING " + host + "\r\n"
# define NICK_message(prefix, newnick)                  prefix + " NICK " + newnick + "\r\n"


#endif