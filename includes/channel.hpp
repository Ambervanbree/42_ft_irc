#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <vector>
# include <map>
# include "user.hpp"

class Channel{
	private:
		std::string					_name; 
		std::string					_topic;
		std::string					_key;
		std::vector<User>			_users;
		size_t						_size;
		std::map<char, bool>		_modes;
		User *						_chop; 	// channel operator

	public:
		Channel(std::string name, User &user);
		~Channel();

		void			initModes();
		void 			setMode();
		void			addUser(std::string key, User &user);
		std::string		getName();
		std::string 	getTopic();
		void 			setTopic(std::string topic);
};

#endif

/* NOTES:
	- Channel is created when a first user joins, this user
	  automatically becomes chanop.
	- Channel ceases to exist when the last user parts.
	- A user can join upto 10 channels
	- Channel operators NICK starts with @ whenever 
	  it is associated with the channel. They can:
		KICK    - Eject a client from the channel
		MODE    - Change the channel's mode
		INVITE  - Invite a client to an invite-only channel (mode +i)
		TOPIC   - Change the channel topic in a mode +t channel
	- Channel message routing:
		channel with one client: messages only go to the server
		channel with two clients: messages are treated as PRVMSG
		channel with more clients: message goes from client 1 to 
			client 2 and then through the server to the rest?
*/