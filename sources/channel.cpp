#include "channel.hpp"

Channel::Channel(std::string name, std::string topic) : _name(name), _topic(topic) {};

Channel::~Channel() {};


// channel is automatically created when 1 client joins it
// ceases to exist when the last client leaves it
// any client can reference an existing channel using its name