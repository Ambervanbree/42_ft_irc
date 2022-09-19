# include "includes/utils.hpp"
# include "includes/commands/parser.hpp"
# include <iostream>

int main(int ac, char **av)
{
	if (ac != 3)
	{
		std::cout << "wrong number of arguments" << std::endl;
		return 1;
	}
	//std::vector<std::string> out;
	User user;
	Channel channel;

	interpretCommand(av[1], user, channel);

	//split_args(av[1], av[2], out);

	//for (unsigned int i = 0; i < out.size(); i++)
	//	std::cout << out[i] << std::endl;
}
