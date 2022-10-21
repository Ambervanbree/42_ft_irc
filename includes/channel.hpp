#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <vector>
# include <map>
# include <set>
# include "commands.hpp"
# include "user.hpp"

class Server;

class Channel{
	private:
		std::string					_name;
		std::string					_key;
		std::string					_topic;
		std::set<User *>			_users;
		std::set<std::string>		_banned;
		std::map<char, bool>		_modes;
		std::set<std::string>		_chop; 		// channel operator
	
	public:
		/* Initialisation */

						Channel(std::string name, User &user);
						~Channel(void);
		void			initModes(void);

		/* Getters */

		std::string				getName(void) const;
		std::string				getTopic(void) const;
		std::set<User *>		getUsers(void) const;
		std::set<std::string>	getBanned(void) const;
		std::string				getModes(void) const;
		std::string				getNames(User &user) const;
		std::string				getBannedList(void);
		size_t					size(void) const;

		/* Message requests */

		void			sendTopic(User &user);
		void			sendChannelMessage(User &user, std::string message);

		/* Checkers */

		bool			onChannel(User &user) const;
		bool			onChannel(std::string nickName) const;
		bool			isBanned(std::string nickMask) const;
		bool			isChop(std::string nickMask) const;
		bool			correctKey(std::string key) const;
		bool			isEmpty(void) const;
		bool			hasChop(void) const;

		/* Setters */

		void			addUser(std::string key, User &user);
		void			setKey(std::string key);
		void			banUser(std::string toBan);
		void			setTopic(std::string newTopic);
		void			addChop(std::string toBan);

		/* Unsetters */

		void 			unsetKey(void);
		void			unbanUser(std::string toUnban);
		void			removeUser(User &user);
		void			removeChop(std::string toRemove);
};

#endif