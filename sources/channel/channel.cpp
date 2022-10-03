#include "channel.hpp"

/******************************************************************************/
/*  Initialisation - constructors and initialisation of modes table
*******************************************************************************/

Channel::Channel(std::string name, User &user) : _name(name) {
	std::cout << "channel " << name << " created" << std::endl;
	initModes();
	_users.insert(&user);
	std::cout << "JOIN message from " << user.getNickname() << " on channel " << getName() << std::endl;
	_chop.insert(user.getNickname());
};

Channel::~Channel() {};

void			Channel::initModes(){
	// TODO --> verify which modes are not necessary
	// _modes['a'] = false; // toggle the anonymous channel flag;
	// _modes['i'] = false; // toggle the invite-only channel flag;;
	// _modes['m'] = false; // toggle the moderated channel
	// _modes['n'] = false; // toggle the no messages to channel from clients on the outside
	// _modes['q'] = false; // toggle the quiet channel flag
	// _modes['p'] = false; // toggle the private channel flag
	// _modes['s'] = false; // toggle the secret channel flag
	// _modes['r'] = false; // toggle the server reop flag
	// _modes['t'] = false; // toggle the topic settable by channel operator only flag

// non toggles:
	_modes['o'] = false; // give/take channel operator privileges
	// 'v'	give/take the voice privilege;
	// 'k'	set/remove the channel key (password);
	// 'l'	set/remove the user limit to channel;
	_modes['b'] = false; // set/remove ban mask to keep users out;
	// 'e'	set/remove an exception mask to override a ban mask;
	// 'I'	set/remove an invitation mask to automatically override the invite-only flag;
}

/******************************************************************************/
/*  Getters
*******************************************************************************/

std::string		Channel::getName() {return _name; }

/******************************************************************************/
/*  Checkers
*******************************************************************************/

bool			Channel::onChannel(User &user){
	return (_users.find(&user) != _users.end());
}

bool			Channel::isBanned(std::string nickMask){
	return (_banned.find(nickMask) != _banned.end());
}

bool			Channel::isChop(std::string nickMask){
	return (_chop.find(nickMask) != _chop.end());
}

bool			Channel::correctKey(std::string key) {
	/* 	
		If key mode is set, mode argument will be cross referenced with the
		given key, else it will be ignored, so true is returned.
	*/

	if (!_key.empty() && (_key != key)){
		return false;
	}
	return true;
}

bool			Channel::isEmpty(){
	return (_users.size() == 0);
}

/******************************************************************************/
/*  Setters
*******************************************************************************/

void			Channel::addUser(std::string key, User &user){
	if (onChannel(user)){
		std::cerr << "ERR_USERONCHANNEL (443)" << std::endl;
		return ;
	}
	if (isBanned(user.getNickname())){
		std::cerr << "ERR_BANNEDFROMCHAN (474)" << std::endl;
		return ; 
	}
	if (key.size() && !correctKey(key)){
		std::cerr << "ERR_BADCHANNELKEY (475)" << std::endl;
		return ;
	}
	_users.insert(&user);
	// channel message: 
	std::cout << "JOIN message from " << user.getNickname() << " on channel " << getName() << std::endl;
	// std::cout << "RPL_TOPIC (332)" << std::endl; // ----> if we decide to include topic
	std::cout << "RPL_NAMREPLY (356)" << std::endl;
	return ;

	/* TODO --> add possible error replies: 
		ERR_INVITEONLYCHAN (473)  -> invite mode
		ERR_CHANNELISFULL (471)   -> limit mode
		ERR_BANNEDFROMCHAN (474)  DONE
		ERR_BADCHANMASK (476)     DONE
	*/
}

void			Channel::setKey(std::string key, std::string userMask) {
	if (!isChop(userMask)){
		std::cerr << "ERR_CHANOPRIVSNEEDED (482)" << std::endl;
		return ;		
	}
	// grammar check key
	std::cout << "Set key to: " << key << std::endl;
	_key = key;
	_modes['k'] = true ;
}

void			Channel::banUser(std::string toBan, std::string userNick){
	if (!isChop(userNick)){
		std::cerr << "ERR_CHANOPRIVSNEEDED (482)" << std::endl;
		return ;		
	}
	if (isBanned(toBan))
		return ;
	std::cout << "Banned user: " << toBan << std::endl;
	_banned.insert(toBan);
	_modes['b'] = true;
}

/******************************************************************************/
/*  Unsetters
*******************************************************************************/

void 			Channel::unsetKey(std::string userNick){
	if (!isChop(userNick)){
		std::cerr << "ERR_CHANOPRIVSNEEDED (482)" << std::endl;
		return ;		
	}
	if (_modes.find('k')->second){
		std::cout << "Key unset" << std::endl;
		_key.clear();
		_modes['k'] = false;
	}
}

void			Channel::unbanUser(std::string toUnban, std::string userNick){
	if (!isChop(userNick)){
		std::cerr << "ERR_CHANOPRIVSNEEDED (482)" << std::endl;
		return ;		
	}
	if (_banned.erase(toUnban)){
		if (_banned.empty())
			_modes['b'] = false;
		std::cout << "Ubanned user: " << toUnban << std::endl;
	}
}

void			Channel::removeUser(User &user, std::string message){
	std::cout << "User " << user.getNickname() << " leaving channel " << getName();
	if (!message.empty())
		std::cout << " with the message \"" << message << "\"" << std::endl;
	else
		std::cout << std::endl;
	_users.erase(&user);
}
