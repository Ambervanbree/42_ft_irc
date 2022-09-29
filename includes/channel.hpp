#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <vector>
# include <map>
# include <set>
# include "user.hpp"

class Channel{
	private:
		std::string					_name; 
		std::string					_key;
		std::set<std::string>		_users;
		std::set<std::string>		_banned;
		std::map<char, bool>		_modes;
		std::set<std::string>		_chop; 	// channel operator

	public:
		/* Initialisation */

		Channel(std::string name, std::string nickMask);
		~Channel();
		void			initModes();

		/* Getters */

		std::string		getName();

		/* Checkers */

		bool			onChannel(std::string nickMask);
		bool			isBanned(std::string nickMask);
		bool			isChop(std::string nickMask);
		bool			correctKey(std::string key);

		/* Setters */

		void			addUser(std::string key, std::string nickMask);
		void			setKey(std::string key, std::string userMask);
		void			banUser(std::string toBan, std::string userNick);

		/* Unsetters */
		void 			unsetKey(std::string userNick);
		void			unbanUser(std::string toUnban, std::string userNick);


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