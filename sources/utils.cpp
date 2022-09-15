#include "../includes/utils.hpp"

void split_args(std::string in, char *delimiter, std::vector<std::string> &out)
{
    char *token = strtok(const_cast<char*>(in.c_str()), delimiter);
    while (token != nullptr)
    {
        out.push_back(std::string(token));
        token = strtok(nullptr, delimiter);
	}
}
