#include "channel.hpp"

/******************************************************************************/
/*  Initialisation - constructors and initialisation of modes table
*******************************************************************************/

Channel::Channel(std::string name, User &user) : _name(name) {
	initModes();
	_users.insert(&user);
	_chop.insert(user.getNickMask());
};

Channel::~Channel() {
	std::cout << "[+] Channel " << _name << " deleted" << std::endl;
};

void			Channel::initModes(){
	_modes['k'] = false; 	//	set/remove the channel key (password)
	_modes['b'] = false; 	//	set/remove ban mask to keep users out
	_modes['t'] = true; 	//	topic settable by chanop only
	_modes['o'] = true; 	//	set/remove chanop priviliges of users
}

/******************************************************************************/
/*  Getters
*******************************************************************************/

std::string				Channel::getName() const {return _name; }
std::string				Channel::getTopic() const {return _topic; }
std::set<User *>		Channel::getUsers() const {return _users; }
std::set<std::string>	Channel::getBanned() const {return _banned; }
std::map<char, bool>	Channel::getModes() const {return _modes; }

/******************************************************************************/
/*  Message requests
*******************************************************************************/

void			Channel::sendTopic(User &user){
	(void)user; 
	// RPL sent to user:
	if (_topic.empty())
		std::cout << "RPL_NOTOPIC (331)" << std::endl;
	else{
		std::cout << "RPL_TOPIC (332)" << std::endl;
		std::cout << "RPL_TOPICWHOTIME (333)" << std::endl;
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

void			Channel::sendChannelMessage(std::string message){
	std::set<User *>::iterator		uit = _users.begin();
	std::set<User *>::iterator		uite = _users.end();
	std::set<std::string>::iterator	cit = _chop.end();

	for (; uit != uite; uit++){
		if (_chop.find((*uit)->getNickMask()) != cit)
			std::cout << message << " from " << "@" << (*uit)->getNickname() << std::endl;
			// send PRIVMSG with nickname ("@" + (*uit)->getNickame())
		else
			std::cout << message << " from" << (*uit)->getNickname() << std::endl;
			// send PRIVMSG with (*uit)->getNickame()
	}
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
	if (!_key.empty() && (_key != key)){
		std::cerr << "ERR_BADCHANNELKEY (475)" << std::endl;
		return false;
	}
	return true;
}

bool			Channel::isEmpty(void) const {
	return (_users.size() == 0);
}

bool			Channel::hasChop(void) const{
	std::map<char, bool>::const_iterator	it = _modes.find('k');

	if (it != _modes.end() && it->second == true)
		return true ;
	return false ;
}

/******************************************************************************/
/*  Setters
*******************************************************************************/

void			Channel::addUser(std::string key, User &user){
	if (onChannel(user))
		std::cerr << "ERR_USERONCHANNEL (443)" << std::endl;
	else if (isBanned(user.getNickMask()))
		std::cerr << "ERR_BANNEDFROMCHAN (474)" << std::endl;
	else if (_modes['k'] == true && !correctKey(key))
		std::cerr << "ERR_BADCHANNELKEY (475)" << std::endl;
	else
		_users.insert(&user);
}

void			Channel::setKey(std::string newKey) {
	_key = newKey;
	_modes['k'] = true ;
}

void			Channel::banUser(std::string toBan){
	_banned.insert(toBan);
	_modes['b'] = true;
}

void			Channel::setTopic(std::string newTopic){
	if (newTopic == ":")
		_topic.clear();
	else
		_topic = newTopic.erase(0, 1);
}

void			Channel::addChop(std::string newChop){
	_chop.insert(newChop);
	_modes['o'] = true;
}

/******************************************************************************/
/*  Unsetters
*******************************************************************************/

void 			Channel::unsetKey(){
	if (_modes['k'] == true){
		_key.clear();
		_modes['k'] = false;
	}
}

void			Channel::unbanUser(std::string toUnban){
	if (_banned.erase(toUnban)){
		if (_banned.empty())
			_modes['b'] = false;
	}
}

void			Channel::removeUser(User &user){
	_users.erase(&user);
}

void			Channel::removeChop(std::string toRemove){
	if (_chop.erase(toRemove)){
		if (_chop.empty())
			_modes['o'] = false;
	}
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