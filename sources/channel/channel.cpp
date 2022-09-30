#include "channel.hpp"

/******************************************************************************/
/*  Initialisation - constructors and initialisation of modes table
*******************************************************************************/

Channel::Channel(std::string name, User &user) : _name(name) {
	std::cout << "channel " << name << " created by " << user.getNickname() << std::endl;
	initModes();
	_chop.insert(user.getNickname());
	_users.insert(&user);
};

Channel::~Channel() {};

void			Channel::initModes(){
	// TODO --> verify which modes are not necessary
	// _modes['o'] = false; // give/take channel operator privileges
	// _modes['p'] = false; // private channel flag
	// _modes['s'] = false; // secret channel flag
	// _modes['i'] = false; // invite-only channel flag
	// _modes['t'] = false; // topic settable by channel operator only flag
	// _modes['n'] = false; // no messages to channel from clients on the outside
	// _modes['m'] = false; // moderated channel
	// _modes['l'] = false; // set the user limit to channel
	_modes['b'] = false; // set a ban mask to keep users out
	// _modes['v'] = false; // give/take the ability to speak on a moderated channel
	_modes['k'] = false; // set a channel key (password)
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

	if (_modes.find('k') != _modes.end() && _key != key){
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
	// TODO --> send standard channel reply message
	std::cout << "user " << user.getNickname() << " is added to " << _name << std::endl;
	_users.insert(&user);
	// TODO --> user.addChannel(*this);
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
	_modes['k'] = true;
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
	if (_modes.find('k') != _modes.end()){
		// TODO ----> should not work if key not set
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
		std::cout << "Ubanned user: " << toUnban << std::endl;
		if (_banned.empty()){
			std::cout << "No more bans on channel." << std::endl;
			_modes['b'] = false;
		}
	}
}

void			Channel::removeUser(User &user){
	_users.erase(&user);
}
