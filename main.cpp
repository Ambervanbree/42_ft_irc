/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 14:58:39 by cproesch          #+#    #+#             */
/*   Updated: 2022/09/14 16:05:59 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include "user.hpp"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Wrong entry - usage : <port number> <password>" << std::endl;
        return 1;
    }
    Server s(atoi(argv[1]), std::string(argv[2]));


    return 0;
}