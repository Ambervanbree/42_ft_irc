#include "../includes/utils.hpp"

void split_args(std::string in, char *delimiter, std::vector<std::string> &out)
{
    char *token = strtok(const_cast<char*>(in.c_str()), delimiter);
    while (token != NULL)
    {
        out.push_back(std::string(token));
        token = strtok(NULL, delimiter);
	}
}

std::vector<std::string> split_on_string(std::string message, std::string delim)
{
	std::vector<std::string> out;
    std::string::size_type start = 0U;
    std::string::size_type end = message.find(delim);
    while (end != std::string::npos)
    {
        out.push_back(message.substr(start, end - start));
        start = end + delim.length();
        end = message.find(delim, start);
    }
    out.push_back(message.substr(start, end));
	return out;
}
