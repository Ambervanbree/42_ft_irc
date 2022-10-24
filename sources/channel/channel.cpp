#include "channel.hpp"

/******************************************************************************/
/*  Initialisation - constructors and initialisation of modes table
*******************************************************************************/

Channel::Channel(std::string name, User &user) : _name(name) {
	initModes();
	_users.insert(&user);
	_chop.insert(user.getNickMask());
	std::cout << "[+] Channel " << name << " created" << std::endl;
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
size_t					Channel::size() const {return _users.size(); }

std::string				Channel::getNames(void) const{
	std::string namesRPL;

	std::set<User *>::iterator 	it = _users.begin();
	std::set<User *>::iterator 	ite = _users.end();

	for (; it != ite; it++){
		namesRPL += " ";
		if (_chop.find((**it).getNickMask()) != _chop.end())
			namesRPL += "@";
		namesRPL += (*it)->getNickname();
	}
	return namesRPL ;
}

std::string				Channel::getModes(void) const{
	std::string						modeString("+");
	std::map<char, bool>::const_iterator	it = _modes.begin();
	std::map<char, bool>::const_iterator	ite = _modes.end();

	for (; it != ite; it++){
		if (it->second == true)
			modeString += it->first;
	}
	return modeString;
}

std::string				Channel::getBannedList(void){
	std::string						bannedList;
	std::set<std::string>::iterator	it = _banned.begin();
	std::set<std::string>::iterator	ite = _banned.end();

	for (; it != ite; it++)
		bannedList += *it;
	return bannedList;	
}


/******************************************************************************/
/*  Message requests
*******************************************************************************/

void			Channel::sendTopic(User &user){
	if (_topic.empty())
		user.addRepliesToBuffer(RPL_NOTOPIC(user.getPrefix(), getName()));
	else{
		user.addRepliesToBuffer(RPL_TOPIC(user.getPrefix(), getName(), getTopic()));
		// user.addRepliesToBuffer(RPL_TOPICWHOTIME(nick, channel, user, setat)) --->> TODO, std::time(0) gets the time, but it's in int. 
	}
}

void			Channel::sendChannelMessage(User &user, std::string message){
	std::string userstring = ":";

	//if (_chop.find(user.getNickMask()) != _chop.end())
	//	userstring += "@";
	userstring += user.getNickMask();
	message.insert(0, userstring);

	std::set<User *>::iterator	it = _users.begin();
	std::set<User *>::iterator	ite = _users.end();

	for (; it != ite; it++)
		(*it)->addRepliesToBuffer(message);
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
	if (!_key.empty() && (_key != key))
		return false;
	return true;
}

bool			Channel::isEmpty(void) const {
	return (_users.size() == 0);
}

bool			Channel::hasChop(void) const{
	std::map<char, bool>::const_iterator	it = _modes.find('o');

	if (it != _modes.end() && it->second == true)
		return true ;
	return false ;
}

/******************************************************************************/
/*  Setters
*******************************************************************************/

void			Channel::addUser(std::string key, User &user){
	if (onChannel(user))
		user.addRepliesToBuffer(ERR_USERONCHANNEL(user.getNickname(), getName()));
	else if (isBanned(user.getNickMask()))
		user.addRepliesToBuffer(ERR_BANNEDFROMCHAN(getName()));
	else if (_modes['k'] == true && !correctKey(key))
		user.addRepliesToBuffer(ERR_BADCHANNELKEY(getName()));
	else{
		_users.insert(&user);
		channelWelcomeMessage(*this, user);
	}
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