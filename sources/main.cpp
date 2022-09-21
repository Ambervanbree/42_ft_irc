#include "server.hpp"
#include "channel.hpp"
#include "user.hpp"

static int check_arg(int argc, char **argv)
{
	if (argc != 3 || std::string(argv[1]).find_first_not_of("0123456789") != std::string::npos)
	{
		std::cerr << "Wrong entry - usage : <port number> <password>" << std::endl;
        return -1;
	}
	int port = atoi(argv[1]);
	if (port < 1025 || port > 65535)
	{
		std::cerr << "Port must be between 1025 and 65535" << std::endl;
		return -1;
	}
	return port;
}

int main(int argc, char *argv[]) 
{
	int port = check_arg(argc, argv);
	if (port == -1)
		return 1;
	    
	User user;
	std::string message = argv[2];

	Server s(port, std::string(argv[2]));
	s.start();
    s.interpretCommand(message, user);
    s.handleConnections();
	std::list<Channel>	_channels;

	// parser.interpretCommand(argv[2], user);
	// s.start();
    // s.handleConnections();
    
	return 0;
}
