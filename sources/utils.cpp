#include "utils.hpp"

/*
Split args : split str into a tab on each caracters of delimiter
- in : str to split
- delimiter : list of delimiters to split
- out : reference to the outpout
*/

void split_args(std::string &in, char *delimiter, std::deque<std::string> &out)
{
    char *token = strtok(const_cast<char*>(in.c_str()), delimiter);
    while (token != NULL)
    {
        out.push_back(std::string(token));
        token = strtok(NULL, delimiter);
	}
}

/*
Split on string : split str into a tab with an entire str is the delimiter
- in : str to split
- delimiter : str delimiter
- out : reference to the outpout
*/

void split_on_string(std::string &message, std::string delim, std::deque<std::string> &out)
{
    std::string::size_type start = 0;
    std::string::size_type end = message.find(delim);
	  std::string to_add;
    while (end != std::string::npos)
    {
		to_add = message.substr(start, end - start);
		if (to_add.size())
        	out.push_back(to_add);
        start = end + delim.length();
        end = message.find(delim, start);
    }
	to_add = message.substr(start, end);
	if (to_add.size())
    	out.push_back(to_add);
}
