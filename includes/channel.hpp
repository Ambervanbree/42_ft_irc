#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <vector>
# include <map>
# include "user.hpp"

class Channel{
	private:
		std::string					_name; 
		//max 200 char, beginning with & or #, 
		//may not contain spaces, a control G, or a comma
		std::string					_topic;
		std::string					_password;
		std::vector<int>			_users;
		std::vector<char>			_modes;
		std::vector<User>			_channelUsers;
		User						*_chop; // channel operator
		// maybe a user history

	public:
		Channel(std::string name, std::string topic);
		~Channel();

		// void join (<channel>{,<channel>} [<key>{,<key>}])
		// server checks if a client is allowed
		//	1.  the user must be invited if the channel is invite-only;
        //   2.  the user's nick/username/hostname must not match any
        //       active bans;
        //   3.  the correct key (password) must be given if it is set.
		// user receives a notice about the commands in the channel
		// MODE, KICK, PART, QUIT and of course PRIVMSG/NOTICE

		void 			setMode();
		std::string 	getTopic();
		void 			setTopic(std::string topic);
		// MODE;
		// TOPIC;
        //    ERR_NEEDMOREPARAMS              ERR_NOTONCHANNEL
        //    RPL_NOTOPIC                     RPL_TOPIC
        //    ERR_CHANOPRIVSNEEDED


		// NAMES;

};


#endif

// JOIN is to join or create a channel, creating user becomes channel operator
// your join can be rejected, depends on the channel mode
// A user can join upto 10 channels
// Channel operators NICK starts with @ whenever it is associated with the channel.
// They can:
        // KICK    - Eject a client from the channel
        // MODE    - Change the channel's mode
        // INVITE  - Invite a client to an invite-only channel (mode +i)
        // TOPIC   - Change the channel topic in a mode +t channel

// channel with one client: messages only go to the server
// channel with two clients: messages are treated as PRVMSG
// channel with more clients: message goes from client 1 to client 2 and then through the server to 3? 
