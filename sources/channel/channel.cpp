#include "channel.hpp"

/******************************************************************************/
/*  Initialisation - constructors and initialisation of modes table
*******************************************************************************/

Channel::Channel(std::string name, User &user) : _name(name) {
	initModes();
	_users.insert(&user);
	std::cout << "JOIN message from " << user.getNickname() << " on new channel " << getName() << std::endl;
	_chop.insert(user.getNickMask());
	// TODO --> If chop sends messages associated with a channel, @ is prefixed to its nickname
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

std::string		Channel::getName() const {return _name; }

/******************************************************************************/
/*  Message requests
*******************************************************************************/

void			Channel::sendTopic(User &user){
	(void)user; 
	// RPL sent to user:
	if (_topic.empty()){
		std::cout << "RPL_NOTOPIC (331)" << std::endl;
		return ;
	}
	else{
		std::cout << "RPL_TOPIC (332)" << std::endl;
		std::cout << "RPL_TOPICWHOTIME (333)" << std::endl;
		return ;
	}
}

void			Channel::sendNames(User &user){
	(void)user;
	// RPL sent to user:
	std::cout << "RPL_NAMREPLY (353)" << std::endl;
	std::cout << "RPL_ENDOFNAMES (366)" << std::endl;			
}

void			Channel::sendList(User &user){
	(void)user;
	// RPL sent to user:
	std::cout << "RPL_LIST (322)" << std::endl;
	std::cout << "RPL_LISTEND (323)" << std::endl;
}

/******************************************************************************/
/*  Checkers
*******************************************************************************/

bool			Channel::onChannel(User &user) const {
	return (_users.find(&user) != _users.end());
}

bool			Channel::onChannel(std::string nickName) const {
	std::set<User *>::iterator	it = _users.begin();
	std::set<User *>::iterator	ite = _users.end();

	for (; it != ite; it++){
		if ((*it)->getNickname() == nickName)
			return true ;
	}
	return false ;
}

bool			Channel::isBanned(std::string nickMask) const {
	return (_banned.find(nickMask) != _banned.end());
}

bool			Channel::isChop(std::string nickMask) const {
	return (_chop.find(nickMask) != _chop.end());
}

bool			Channel::correctKey(std::string key) const {
	/* 	
		If key mode is set, mode argument will be cross referenced with the
		given key, else it will be ignored, so true is returned.
	*/

	if (!_key.empty() && (_key != key)){
		return false;
	}
	return true;
}

bool			Channel::isEmpty() const {
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
	if (isBanned(user.getNickMask())){
		std::cerr << "ERR_BANNEDFROMCHAN (474)" << std::endl;
		return ; 
	}
	if (_modes['k'] == true && !correctKey(key)){
		std::cerr << "ERR_BADCHANNELKEY (475)" << std::endl;
		return ;
	}
	_users.insert(&user);
	// RPL sent to channel (including user):
	std::cout << "[+] JOIN message from " << user.getNickname() << " on channel " << getName() << std::endl;
	// RPL sent to user:
	std::cout << "RPL_TOPIC (332)" << std::endl;
	std::cout << "RPL_NAMREPLY (356)" << std::endl;
	return ;

	/* TODO --> add possible error replies: 
		ERR_INVITEONLYCHAN (473)  -> invite mode
		ERR_CHANNELISFULL (471)   -> limit mode
	*/
}

void			Channel::setKey(std::string newKey, std::string nickMask) {
	if (!isChop(nickMask)){
		std::cerr << "ERR_CHANOPRIVSNEEDED (482)" << std::endl;
		return ;		
	}
	std::cout << "[+] MODE message: Set key to: " << newKey << std::endl;
	_key = newKey;
	_modes['k'] = true ;
}

void			Channel::banUser(std::string toBan, std::string nickMask){
	if (!isChop(nickMask)){
		std::cerr << "ERR_CHANOPRIVSNEEDED (482)" << std::endl;
		return ;		
	}
	if (isBanned(toBan))
		return ;
	std::cout << "[+] MODE message: Banned user: " << toBan << std::endl;
	_banned.insert(toBan);
	_modes['b'] = true;
}

void			Channel::setTopic(std::string newTopic, std::string nickMask){
	// if (_modes['t'] == true && !isChop(nickMask)){
	// 	std::cerr << "ERR_CHANOPRIVSNEEDED (482)" << std::endl;
	// 	return ;
	// }
	(void)nickMask; // TODO --> this is needed if mode 't' is implemented
	if (newTopic == ":") {
		_topic.clear();
		// send to channel:
		std::cout << "[+] MODE message: Topic is cleared" << std::endl;
	}
	else{
		_topic = newTopic.erase(0, 1);
		// send to channel:
		std::cout << "[+] MODE message: New channel topic: " << _topic << std::endl;
	}
}

/******************************************************************************/
/*  Unsetters
*******************************************************************************/

void 			Channel::unsetKey(std::string nickMask){
	if (!isChop(nickMask)){
		std::cerr << "ERR_CHANOPRIVSNEEDED (482)" << std::endl;
		return ;		
	}
	if (_modes.find('k')->second){
		std::cout << "[+] MODE message: key unset" << std::endl;
		_key.clear();
		_modes['k'] = false;
	}
}

void			Channel::unbanUser(std::string toUnban, std::string nickMask){
	if (!isChop(nickMask)){
		std::cerr << "ERR_CHANOPRIVSNEEDED (482)" << std::endl;
		return ;		
	}
	if (_banned.erase(toUnban)){
		if (_banned.empty())
			_modes['b'] = false;
		std::cout << "[+] MODE message: Unbanned user: " << toUnban << std::endl;
	}
}

void			Channel::removeUser(User &user, std::string message){
	std::cout << "[+] PART message: User " << user.getNickname() << " leaving channel " << getName();
	if (!message.empty())
		std::cout << " with the message \"" << message << "\"" << std::endl;
	else
		std::cout << std::endl;
	_users.erase(&user);
}


/******************************************************************************/
/*  Non member overload
*******************************************************************************/

bool			operator<(const Channel &lhs, const Channel &rhs){
	return lhs.getName() < rhs.getName();
}

bool			operator==(const Channel &lhs, const Channel &rhs){
	return lhs.getName() == rhs.getName();
}