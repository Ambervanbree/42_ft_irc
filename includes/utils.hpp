#ifndef UTILS_HPP
# define UTILS_HPP
# include <vector>
# include <string>
# include <cstring>
# include <iostream>
# include <sstream>
# include <ctime>
# include <iostream>

void 		split_args(std::string &in, char *delimiter, std::vector<std::string> &out);
void 		split_on_string(std::string &message, std::string delim, std::vector<std::string> &out);
std::string	toString(size_t number);
int			getTime(void);

#endif