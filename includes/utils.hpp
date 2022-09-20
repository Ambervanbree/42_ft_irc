#ifndef UTILS_HPP
# define UTILS_HPP
# include <deque>
# include <string>
# include <cstring>
# include <vector>

void split_args(std::string in, char *delimiter, std::vector<std::string> &out);
std::deque<std::string> split_on_string(std::string message, std::string delim);

#endif