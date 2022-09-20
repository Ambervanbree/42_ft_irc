#ifndef UTILS_HPP
# define UTILS_HPP
# include <vector>
# include <string>
# include <cstring>


void split_args(std::string in, char *delimiter, std::vector<std::string> &out);
std::vector<std::string> split_on_string(std::string message, std::string delim);

#endif