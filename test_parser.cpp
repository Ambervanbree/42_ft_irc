/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 12:28:46 by cmorel-a          #+#    #+#             */
/*   Updated: 2022/09/15 12:38:22 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"
# include <iostream>

int main(int ac, char **av)
{
	if (ac != 3)
	{
		std::cout << "wrong number of arguments" << std::endl;
		return 1;
	}
	std::vector<std::string> out;
	split_args(av[1], av[2], out);

	std::vector<std::string>::iterator it = out.begin();
	std::vector<std::string>::iterator ite = out.end();
	for (; it != ite; it++)
		std::cout << *it << std::endl;

}