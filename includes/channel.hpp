#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <vector>
# include <map>
# include <set>
# include "user.hpp"

class Server;
// class User;

class Channel{
	private:
		std::string					_name; 
		std::string					_key;
		std::string					_topic;
		std::set<User *>			_users;
		std::set<std::string>		_banned;
		// std::set<std::string>		_invite;
		std::map<char, bool>		_modes;
		std::set<std::string>		_chop; 	// channel operator

	public:
		/* Initialisation */

		Channel(std::string name, User &user);
		~Channel();
		void			initModes();

		/* Getters */

		std::string		getName() const;

		/* Message requests */

		void			sendTopic(User &user);
		void			sendNames(User &user);
		void			sendList(User &user);

		/* Checkers */

		bool			onChannel(User &user) const;
		bool			onChannel(std::string nickName) const;
		bool			isBanned(std::string nickMask) const;
		bool			isChop(std::string nickMask) const;
		bool			correctKey(std::string key) const;
		bool			isEmpty() const;

		/* Setters */

		void			addUser(std::string key, User &user);
		void			setKey(std::string key);
		void			banUser(std::string toBan);
		void			setTopic(std::string newTopic);

		/* Unsetters */
		void 			unsetKey(std::string userNick);
		void			unbanUser(std::string toUnban);
		void			removeUser(User &user, std::string message);
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