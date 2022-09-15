/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 12:41:40 by cproesch          #+#    #+#             */
/*   Updated: 2022/09/14 17:52:33 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

Server::Server(int port, std::string password)
: _port(port), _password(password), _nbUsers(0)  {
    _serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    _serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    _serverAddr.sin_family = AF_INET;
    _serverAddr.sin_port = htons(_port);

/*-----------BINDING-----------*/

    bind(_serverSocket, (const struct sockaddr *) &_serverAddr, sizeof(_serverAddr));
    std::cout << "[+] The server socket has fd nb " << _serverSocket << std::endl;

/*-----------LISTENING-----------*/

    if (listen(_serverSocket, 5) == 0)
        std::cout << "[+] Server is listening" << std::endl;
    else
        std::cout << "[+] Error not listening" << std::endl;


// Ici DEBUT boucle
    struct sockaddr_in addrClient;
    socklen_t csize = sizeof(addrClient);

/*-----------ACCEPTING CONNECTION-----------*/

    _users[_nbUsers] = accept(_serverSocket, (struct sockaddr *) & addrClient, &csize);
    if (_users[_nbUsers] > 0){
        std::cout << "[+] Connection accepted with client fd nb " << _users[_nbUsers] << std::endl;
    }
    else
        std::cout << "[+] Error while accepting" << std::endl;
    char msg[5];

/*-----------RECIEVING MESSAGE-----------*/

    int res = recv(_users[_nbUsers], msg, 5, 0);
    if (res >= 0)
        std::cout << "[+] Client message is '" << msg << "' with nb characters " << res << std::endl;
    else
        std::cout << "[+] Error while recieving" << std::endl;

/*-----------CLOSING-----------*/

    if (close(_users[_nbUsers]) == 0 && close(_serverSocket) == 0)
        std::cout << "[+] All sockets closed" << std::endl;
    else
        std::cout << "[+] Error while closing" << std::endl;

    _nbUsers++;
// Ici FIN boucle

}

Server::~Server(void) {}
