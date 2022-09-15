/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <cmorel-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 12:18:00 by cmorel-a          #+#    #+#             */
/*   Updated: 2022/09/15 12:36:09 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP
# include <vector>
# include <string>
# include <cstring>


void split_args(std::string in, char *delimiter, std::vector<std::string> &out);

#endif