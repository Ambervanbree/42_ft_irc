#ifndef REPLIES_HPP
# define REPLIES_HPP
# include <string>

/* Registration RPL */

# define RPL_WELCOME(nickmask)                  "001 :Welcome to the Internet Relay Network, " + nickmask + "\r\n"

/* RPL */

# define RPL_UMODEIS(mode)			            "221 " + mode + "\r\n"
# define RPL_WHOISUSER(nick, user, realname)	"311 " + nick + " " + user + " localhost " + realname + "\r\n"
# define RPL_WHOISSERVER(nick, server, info)	"312 " + nick + " " + server + " :" + info "\r\n"
# define RPL_WHOISOPERATOR(nick)				"313 " + nick + " :is an IRC operator\r\n"
# define RPL_WHOISIDLE(nick, idle, signon)		"317 " + nick + " " + idle + " " + signon + " :seconds idle, signon time\r\n"
# define RPL_ENDOFWHOIS(nick)					"318 " + nick + " :End of /WHOIS list\r\n"
# define RPL_LIST(channel, nbuser, topic)	  	"322 " + channel + " " + nbuser + " :" + topic + "\r\n"
# define RPL_LISTEND	       				    "323 :End of /LIST\r\n"
# define RPL_CHANNELMODEIS(chan, modestr)       "324 " + chan + " " + modestr + "\r\n"
# define RPL_NOTOPIC(channel)			        "331 " + channel + " :No topic is set\r\n"
# define RPL_TOPIC(channel, topic)      	    "332 " + channel + " :" + topic + "\r\n"
//# define RPL_TOPICWHOTIME(nick, channel, user, setat)   "333 " + nick + " " + channel + " " + user + " " + setat + "\r\n"
# define RPL_INVITING(channel, invitee)         "341 " + channel + " " + invitee + "\r\n"
# define RPL_NAMREPLY(channel, users)   		"353  = " + channel + " :" + users + "\r\n"
# define RPL_ENDOFNAMES(channel)                "366 " + channel +  " :End of /NAMES list\r\n"
# define RPL_BANLIST(channel, masks)		    "367 " + channel + " " + masks + "\r\n"
# define RPL_ENDOFBANLIST(channel)		        "368 " + channel + " :End of channel ban list\r\n"
# define RPL_MOTD(comment) 			            "372 :" + comment + "\r\n"
# define RPL_MOTDSTART					        "375 :- IRC Message of the day - \r\n"
# define RPL_ENDOFMOTD					        "376 :End of /MOTD command\r\n"
# define RPL_YOUREOPER				            "381 :You are now an IRC operator\r\n"

/* ERR */

# define ERR_NOSUCHNICK(nick)     	            "401 " + nick + " :No such nick/channel\r\n"
# define ERR_NOSUCHSERVER(server)          		"402 " + server + " :No such server\r\n"   
# define ERR_NOSUCHCHANNEL(channel)				"403 " + channel + " :No such channel\r\n"
# define ERR_CANNOTSENDTOCHAN(channel)	        "404 " + channel + " :Cannot send to channel\r\n"
# define ERR_TOOMANYCHANNELS(channel)			"405 " + channel + " :You have joined too many channels\r\n"
# define ERR_TOOMANYTARGETS						"407 :Too many targets specified\r\n"
# define ERR_NORECIPIENT						"411 :No recipient specified\r\n"
# define ERR_NOTEXTTOSEND						"412 :No text to send\r\n"
# define ERR_UNKNOWNCOMMAND(cmd_name)           "421 " + cmd_name + " :Command not found: " + cmd_name + "\r\n"
# define ERR_NOMOTD								"422 :MOTD File is missing\r\n"
# define ERR_NONICKNAMEGIVEN					"431 :No nickname given\r\n"
# define ERR_ERRONEUSNICKNAME(nick)				"432 " + nick + " :Erroneous nickname\r\n"
# define ERR_NICKNAMEINUSE(nick)				"433 " + nick + " :Nickname is already in user\r\n"
# define ERR_USERNOTINCHANNEL(nick, channel)	"441 " + nick + " " + channel + " :They aren't on that channel\r\n"
# define ERR_NOTONCHANNEL(channel)	        	"442 " + channel + " :You're not on that channel\r\n"
# define ERR_USERONCHANNEL(nick, channel)		"443 " + nick + " " + channel + " :is already on channel\r\n"
# define ERR_NEEDMOREPARAMS(cmd_name)		    "461 " + cmd_name + " :Not enough parameters\r\n"
# define ERR_ALREADYTREGISTERED	        		"462 :Unauthorized command (already registered)\r\n"
# define ERR_PASSWDMISMATCH						"464 :Password incorrect\r\n"
# define ERR_UNKNOWNMODE(flag)			        "472 " + flag + " :is unknown mode char to me\r\n"
# define ERR_BANNEDFROMCHAN(channel)			"474 " + channel + " :Cannot join channel (+b)\r\n"
# define ERR_BADCHANNELKEY(channel)				"475 " + channel + " :Cannot join channel (+k)\r\n"
# define ERR_BADCHANMASK(channel)				"476 " + channel + " :Bad Channel Mask\r\n"
# define ERR_NOPRIVILEGES                       "481 :Permission Denied- You're not an IRC operator\r\n"
# define ERR_CHANPRIVSNEEDED(channel)	    	"482 " + channel + " :You're not channel operator\r\n"
# define ERR_NOOPERHOST     					"491 :No O-lines for your host\r\n"
# define ERR_UMODEUNKNOWMFLAG               	"501 :Unknown :MODE flag\r\n"
# define ERR_NOORIGIN                           "409 :No origin specified\r\n"

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
# define ERROR_message(reason)                          " ERROR :Closing Link: " + reason + "\r\n"
# define QUIT_message(leaver, reason)                   ":" + leaver + " QUIT :" + reason + "\r\n"
# define PONG_message(host)                             "PONG " + host + "\r\n"

#endif