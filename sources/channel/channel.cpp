#include "channel.hpp"

// channel is automatically created when 1 client joins it
// ceases to exist when the last client leaves it
// any client can reference an existing channel using its name

Channel::Channel(std::string name, User &user) : _name(name) {
	_chop = user;
	_users.push_back(user);
	_size++;
	initModes();
};

Channel::~Channel() {};

void 			Channel::setMode(){
	// modes are giving like this: <channel> {[+|-]|o|p|s|i|t|n|b|v} [<limit>] [<user>] [<ban mask>]
}

std::string 	Channel::getTopic() {return _topic; }

void 			Channel::setTopic(std::string new_topic) {
	_topic = new_topic;
}

void			Channel::initModes(){
	_modes['o'] = false; // give/take channel operator privileges
	_modes['p'] = false; // private channel flag
	_modes['s'] = false; // secret channel flag
	_modes['i'] = false; // invite-only channel flag
	_modes['t'] = false; // topic settable by channel operator only flag
	_modes['n'] = false; // no messages to channel from clients on the outside
	_modes['m'] = false; // moderated channel
	_modes['l'] = false; // set the user limit to channel
	_modes['b'] = false; // set a ban mask to keep users out
	_modes['v'] = false; // give/take the ability to speak on a moderated channel
	_modes['k'] = false; // set a channel key (password)
}

void			Channel::addUser(User &user){
	*(_users.end()) = user;
	_size++;
}


// void	Channel::setChannelModes(){
// 	_channelModes['o'] = "give/take channel operator privileges";
// 	_channelModes['p'] = "private channel flag";
// 	_channelModes['s'] = "secret channel flag";
// 	_channelModes['i'] = "invite=only channel flag";
// 	_channelModes['t'] = "topic settable by channel operator only flag";
// 	_channelModes['n'] = "no messages to channel from clients on the outside";
// 	_channelModes['m'] = "moderated channel";
// 	_channelModes['l'] = "set the user limit to channel";
// 	_channelModes['b'] = "set a ban mask to keep users out";
// 	_channelModes['v'] = "give/take the ability to speak on a moderated channel";
// 	_channelModes['k'] = "set a channel key (password)";
// }