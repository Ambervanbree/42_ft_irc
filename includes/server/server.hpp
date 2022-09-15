/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 12:35:52 by cproesch          #+#    #+#             */
/*   Updated: 2022/09/14 17:41:46 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <iomanip>
# include <cstdlib>
# include <string.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <arpa/inet.h>
# include <unistd.h>

class Server {

public:
    Server(int port, std::string password);
    ~Server(void);

private:
    int                 _port;
    std::string         _password;
    id_t                _nbUsers;
    int                 _serverSocket;
    struct sockaddr_in  _serverAddr;
    int                 *_users;
    int                 *_channels;
    
    Server(void);
    Server(const Server &rhs);
    Server &operator= (const Server &rhs);

};

#endif