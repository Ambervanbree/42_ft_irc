/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 12:16:21 by cmorel-a          #+#    #+#             */
/*   Updated: 2022/09/15 14:22:41 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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