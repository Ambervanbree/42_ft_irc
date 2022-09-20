#include "channel.hpp"

Channel::Channel(std::string name, std::string topic) : _name(name), _topic(topic) {
	setModes();
};

Channel::~Channel() {};

// void Channel::join() {};

void 			Channel::setModes(){
	// modes are giving like this: <channel> {[+|-]|o|p|s|i|t|n|b|v} [<limit>] [<user>] [<ban mask>]
	_channelModes['o'] = "give/take channel operator privileges";
	_channelModes['p'] = "private channel flag";
	_channelModes['s'] = "secret channel flag";
	_channelModes['i'] = "invite=only channel flag";
	_channelModes['t'] = "topic settable by channel operator only flag";
	_channelModes['n'] = "no messages to channel from clients on the outside";
	_channelModes['m'] = "moderated channel";
	_channelModes['l'] = "set the user limit to channel";
	_channelModes['b'] = "set a ban mask to keep users out";
	_channelModes['v'] = "give/take the ability to speak on a moderated channel";
	_channelModes['k'] = "set a channel key (password)";
}

std::string 	Channel::getTopic() {return _topic; }

void 			Channel::setTopic(std::string new_topic) {
	_topic = new_topic;
}



// channel is automatically created when 1 client joins it
// ceases to exist when the last client leaves it
// any client can reference an existing channel using its name