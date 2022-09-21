#ifndef UTILS_HPP
# define UTILS_HPP
# include <deque>
# include <string>
# include <cstring>

void split_args(std::string &in, char *delimiter, std::deque<std::string> &out);
void split_on_string(std::string &message, std::string delim, std::deque<std::string> &out);

#endif