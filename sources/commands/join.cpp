#include "channel.hpp"
#include "parser.hpp"
#include "user.hpp"

#define CHANNEL1 command[0]
#define CHANNEL2 command[1]
#define KEY1 command[2]
#define KEY2 command[3]

// JOIN <channel>
// -> Check if a client is allowed to join a channel.
// Doesn't work yet, because the list of channels in the server is needed
void JOIN(std::vector<std::string> command, User& user)
{
	Channel	join1 = _channel.find(CHANNEL1);

	if (join != _channel.end())
		join.addUser(KEY1);
	else
		join = Channel(CHANNEL1, user);
	
	
}
