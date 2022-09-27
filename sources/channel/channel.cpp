#include "channel.hpp"

Channel::Channel(std::string name, User &user) : _name(name) {
	std::cout << "channel " << name << " created by " << user.getNickname() << std::endl;
	initModes();
	_chop = &user;
	_users.push_back(user);
	_size++;
};

Channel::~Channel() {};

void 			Channel::setMode(std::string &modestring, std::string &modesarg){
	(void)modestring;
	(void)modesarg;
	// Mode command: 
	// <channel> {[+|-]|o|p|s|i|t|n|b|v} [<limit>] [<user>] [<ban mask>]
}

void 			Channel::unsetMode(std::string &modestring, std::string &modesarg){
	(void)modestring;
	(void)modesarg;
	// Mode command: 
	// <channel> {[+|-]|o|p|s|i|t|n|b|v} [<limit>] [<user>] [<ban mask>]
}

std::string 	Channel::getTopic() {return _topic; }

std::string		Channel::getName() {return _name; }

void 			Channel::setTopic(std::string new_topic) {
	_topic = new_topic; 
	// TODO --> grammar check + RPL
}

void			Channel::initModes(){
	// TODO --> verify which modes are not necessary
	// _modes['o'] = false; // give/take channel operator privileges
	// _modes['p'] = false; // private channel flag
	// _modes['s'] = false; // secret channel flag
	// _modes['i'] = false; // invite-only channel flag
	_modes['t'] = false; // topic settable by channel operator only flag
	// _modes['n'] = false; // no messages to channel from clients on the outside
	// _modes['m'] = false; // moderated channel
	// _modes['l'] = false; // set the user limit to channel
	// _modes['b'] = false; // set a ban mask to keep users out
	// _modes['v'] = false; // give/take the ability to speak on a moderated channel
	_modes['k'] = false; // set a channel key (password)
}

void			Channel::addUser(std::string key, User &user){
	if (onChannel(user)){
		std::cerr << "ERR_USERONCHANNEL (443)" << std::endl;
		return ;
	}
	if (isBanned(user)){
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
	_size++;
	// TODO --> user.addChannel(*this);
	return ;

	/* TODO --> add possible error replies: 
		ERR_INVITEONLYCHAN (473)  -> invite mode
		ERR_CHANNELISFULL (471)   -> limit mode
		ERR_BANNEDFROMCHAN (474)  DONE
		ERR_BADCHANMASK (476)     DONE
	*/
}

bool			Channel::onChannel(User &user){
	std::vector<User>::iterator	it = _users.begin();
	std::vector<User>::iterator ite = _users.end();

	for (; it != ite; it++){
		if (it->getNickname() == user.getNickname())
			return true;
	}
	return false;
}

bool			Channel::isBanned(User &user){
	std::vector<User>::iterator	it = _banned.begin();
	std::vector<User>::iterator ite = _banned.end();

	for (; it != ite; it++){
		if (it->getNickname() == user.getNickname())
			return true;
	}
	return false;
}

bool			Channel::isChop(User &user){
	std::vector<User>::iterator	it = _chop.begin();
	std::vector<User>::iterator ite = _chop.end();

	for (; it != ite; it++){
		if (it->getNickname() == user.getNickname())
			return true;
	}
	return false;
}

void			Channel::setKey(std::string key) {
	_key = key; 
}

bool			Channel::correctKey(std::string key) {
	if (_modes.find('k') != _modes.end() && _key != key){
		return false;
	}
	return true;
}

void			Channel::banUser(std::string nickMask){
	_banned.push_back(nickMask);
	// send to user: ERR_BANNEDFROMCHAN (474)
}