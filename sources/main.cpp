#include "server.hpp"
//#include "user.hpp"

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
    Server s(port, std::string(argv[2]));
    return 0;
}