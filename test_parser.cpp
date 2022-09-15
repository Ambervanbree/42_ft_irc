/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 12:28:46 by cmorel-a          #+#    #+#             */
/*   Updated: 2022/09/15 14:25:42 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/utils.hpp"
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

	for (int i = 0; i < out.size(); i++)
		std::cout << out[i] << std::endl;

}