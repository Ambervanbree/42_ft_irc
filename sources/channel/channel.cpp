#include "channel.hpp"

/******************************************************************************/
/*  Initialisation - constructors and initialisation of modes table
*******************************************************************************/

Channel::Channel(std::string name, User &user) : _name(name) {
	std::cout << "channel " << name << " created by " << user.getNickname() << std::endl;
	initModes();
	_chop.push_back(user.getNickname());
	_users.push_back(user);
};

Channel::~Channel() {};

void 			Channel::setMode(std::string &modestring, std::string &modesarg){
	(void)modestring;
	(void)modesarg;
	// Mode command: 
	// <channel> {[+|-]|o|p|s|i|t|n|b|v} [<limit>] [<user>] [<ban mask>]
}

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
	std::vector<User>::iterator	it = _users.begin();
	std::vector<User>::iterator ite = _users.end();

	for (; it != ite; it++){
		if (it->getNickname() == user.getNickname())
			return true;
	}
	return false;
}

bool			Channel::isBanned(std::string nickMask){
	std::vector<std::string>::iterator	it = _banned.begin();
	std::vector<std::string>::iterator ite = _banned.end();

	for (; it != ite; it++){
		if (*it == nickMask)
			return true;
	}
	return false;
}

bool			Channel::isChop(User &user){
	std::vector<std::string>::iterator	it = _chop.begin();
	std::vector<std::string>::iterator 	ite = _chop.end();

	for (; it != ite; it++){
		if (*it == user.getNickname())
			return true;
	}
	return false;
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
	if (!correctKey(key)){
		std::cerr << "ERR_BADCHANNELKEY (475)" << std::endl;
		return ;
	}
	// TODO --> send standard channel reply message
	std::cout << "user " << user.getNickname() << " is added to " << _name << std::endl;
	_users.push_back(user);
	// TODO --> user.addChannel(*this);
	return ;

	/* TODO --> add possible error replies: 
		ERR_INVITEONLYCHAN (473)  -> invite mode
		ERR_CHANNELISFULL (471)   -> limit mode
		ERR_BANNEDFROMCHAN (474)  DONE
		ERR_BADCHANMASK (476)     DONE
	*/
}

void			Channel::setKey(std::string key, User &user) {
	if (!isChop(user)){
		std::cerr << "ERR_CHANOPRIVSNEEDED (482)" << std::endl;
		return ;		
	}
	// grammar check key
	std::cout << "Set key to: " << key << std::endl;
	_key = key;
	_modes['k'] = true;
}

void			Channel::banUser(std::string nickMask, User &user){
	if (!isChop(user)){
		std::cerr << "ERR_CHANOPRIVSNEEDED (482)" << std::endl;
		return ;		
	}
	if (isBanned(nickMask))
		return ;
	std::cout << "Banned user: " << nickMask << std::endl;
	_banned.push_back(nickMask);
	_modes['b'] = true;
}

/******************************************************************************/
/*  Unsetters
*******************************************************************************/

void 			Channel::unsetKey(User &user){
	if (!isChop(user)){
		std::cerr << "ERR_CHANOPRIVSNEEDED (482)" << std::endl;
		return ;		
	}
	_key.clear();
	_modes['k'] = false;
}

void			Channel::unbanUser(std::string nickMask, User &user){
	if (!isChop(user)){
		std::cerr << "ERR_CHANOPRIVSNEEDED (482)" << std::endl;
		return ;		
	}
// find and ban user
}
