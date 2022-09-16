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
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <errno.h>

#define TRUE             1
#define FALSE            0

Server::Server(int port, std::string password)
: _port(port), _password(password), _nbUsers(0)  {
    struct pollfd fds[200];
    int nfds = 1, current_size = 0, i, j;
    int desc_ready, end_server = FALSE, compress_array = FALSE;
    int new_sd = -1;
    int close_conn;
    char   buffer[80];
    int len;
    int    timeout;

    _serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    memset(&_serverAddr, 0, sizeof(_serverAddr));
    _serverAddr.sin_family = AF_INET;
    memcpy(&_serverAddr.sin_addr, &in6addr_any, sizeof(in6addr_any));
    _serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    _serverAddr.sin_port = htons(_port);

  /*************************************************************/
  /* Allow socket descriptor to be reuseable                   */
  /*************************************************************/
    int rc;
    int on = 1;
    rc = setsockopt(_serverSocket, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));
    if (rc < 0)
    {
        perror("setsockopt() failed");
        close(_serverSocket);
    }

    /*************************************************************/
    /* Set socket to be nonblocking. All of the sockets for      */
    /* the incoming connections will also be nonblocking since   */
    /* they will inherit that state from the listening socket.   */
    /*************************************************************/
    rc = ioctl(_serverSocket, FIONBIO, (char *)&on);
    if (rc < 0)
    {
        perror("ioctl() failed");
        close(_serverSocket);
    }

/*-----------BINDING-----------*/

    rc = bind(_serverSocket, (const struct sockaddr *) &_serverAddr, sizeof(_serverAddr));
    std::cout << "[+] The server socket has fd nb " << _serverSocket << std::endl;
    if (rc < 0)
    {
        perror("bind() failed");
        close(_serverSocket);
    }
/*-----------LISTENING-----------*/

    if (listen(_serverSocket, 5) == 0)
        std::cout << "[+] Server is listening" << std::endl;
    else
        std::cout << "[+] Error not listening" << std::endl;


// Ici DEBUT boucle
/*************************************************************/
/* Initialize the pollfd structure                           */
/*************************************************************/
  memset(fds, 0 , sizeof(fds));

/*************************************************************/
/* Set up the initial listening socket                        */
/*************************************************************/
    fds[0].fd = _serverSocket;
    fds[0].events = POLLIN;
    
/*************************************************************/
/* Initialize the timeout to 3 minutes. If no                */
/* activity after 3 minutes this program will end.           */
/* timeout value is based on milliseconds.                   */
/*************************************************************/
    timeout = (3 * 60 * 1000);

/*************************************************************/
/* Loop waiting for incoming connects or for incoming data   */
/* on any of the connected sockets.                          */
/*************************************************************/
    do
    {
    /***********************************************************/
    /* Call poll() and wait 3 minutes for it to complete.      */
    /***********************************************************/
        printf("Waiting on poll()...\n");
        rc = poll(fds, nfds, timeout);

    /***********************************************************/
    /* Check to see if the poll call failed.                   */
    /***********************************************************/
        if (rc < 0)
        {
        perror("  poll() failed");
        break;
        }

    /***********************************************************/
    /* Check to see if the 3 minute time out expired.          */
    /***********************************************************/
        if (rc == 0)
        {
        printf("  poll() timed out.  End program.\n");
        break;
        }


    /***********************************************************/
    /* One or more descriptors are readable.  Need to          */
    /* determine which ones they are.                          */
    /***********************************************************/
        current_size = nfds;
        for (i = 0; i < current_size; i++)
        {
    /*********************************************************/
    /* Loop through to find the descriptors that returned    */
    /* POLLIN and determine whether it's the listening       */
    /* or the active connection.                             */
    /*********************************************************/
        if(fds[i].revents == 0)
            continue;

    /*********************************************************/
    /* If revents is not POLLIN, it's an unexpected result,  */
    /* log and end the server.                               */
    /*********************************************************/
        if(fds[i].revents != POLLIN)
        {
            printf("  Error! revents = %d\n", fds[i].revents);
            end_server = TRUE;
            break;

        }
        if (fds[i].fd == _serverSocket)
        {
        /*******************************************************/
        /* Listening descriptor is readable.                   */
        /*******************************************************/
            printf("  Listening socket is readable\n");

        /*******************************************************/
        /* Accept all incoming connections that are            */
        /* queued up on the listening socket before we         */
        /* loop back and call poll again.                      */
        /*******************************************************/
            do
            {
        /*****************************************************/
        /* Accept each incoming connection. If               */
        /* accept fails with EWOULDBLOCK, then we            */
        /* have accepted all of them. Any other              */
        /* failure on accept will cause us to end the        */
        /* server.                                           */
        /*****************************************************/
            new_sd = accept(_serverSocket, NULL, NULL);
            if (new_sd < 0)
            {
                if (errno != EWOULDBLOCK)
                {
                perror("  accept() failed");
                end_server = TRUE;
                }
                break;
            }

        /*****************************************************/
        /* Add the new incoming connection to the            */
        /* pollfd structure                                  */
        /*****************************************************/
            printf("  New incoming connection - %d\n", new_sd);
            fds[nfds].fd = new_sd;
            fds[nfds].events = POLLIN;
            nfds++;

        /*****************************************************/
        /* Loop back up and accept another incoming          */
        /* connection                                        */
        /*****************************************************/
            } while (new_sd != -1);
        }

    /*********************************************************/
    /* This is not the listening socket, therefore an        */
    /* existing connection must be readable                  */
    /*********************************************************/

        else
        {
            printf("  Descriptor %d is readable\n", fds[i].fd);
            close_conn = FALSE;
        /*******************************************************/
        /* Receive all incoming data on this socket            */
        /* before we loop back and call poll again.            */
        /*******************************************************/

            do
            {
        /*****************************************************/
        /* Receive data on this connection until the         */
        /* recv fails with EWOULDBLOCK. If any other         */
        /* failure occurs, we will close the                 */
        /* connection.                                       */
        /*****************************************************/
            rc = recv(fds[i].fd, buffer, sizeof(buffer), 0);
            if (rc < 0)
            {
                if (errno != EWOULDBLOCK)
                {
                perror("  recv() failed");
                close_conn = TRUE;
                }
                break;
            }

        /*****************************************************/
        /* Check to see if the connection has been           */
        /* closed by the client                              */
        /*****************************************************/
            if (rc == 0)
            {
                printf("  Connection closed\n");
                close_conn = TRUE;
                break;
            }

        /*****************************************************/
        /* Data was received                                 */
        /*****************************************************/
            len = rc;
            printf("  %d bytes received\n", len);

        /*****************************************************/
        /* Echo the data back to the client                  */
        /*****************************************************/
            rc = send(fds[i].fd, buffer, len, 0);
            if (rc < 0)
            {
                perror("  send() failed");
                close_conn = TRUE;
                break;
            }

            } while(TRUE);

        /*******************************************************/
        /* If the close_conn flag was turned on, we need       */
        /* to clean up this active connection. This            */
        /* clean up process includes removing the              */
        /* descriptor.                                         */
        /*******************************************************/
            if (close_conn)
            {
            close(fds[i].fd);
            fds[i].fd = -1;
            compress_array = TRUE;
            }


        }  /* End of existing connection is readable             */
        } /* End of loop through pollable descriptors              */

    /***********************************************************/
    /* If the compress_array flag was turned on, we need       */
    /* to squeeze together the array and decrement the number  */
    /* of file descriptors. We do not need to move back the    */
    /* events and revents fields because the events will always*/
    /* be POLLIN in this case, and revents is output.          */
    /***********************************************************/
        if (compress_array)
        {
        compress_array = FALSE;
        for (i = 0; i < nfds; i++)
        {
            if (fds[i].fd == -1)
            {
            for(j = i; j < nfds; j++)
            {
                fds[j].fd = fds[j+1].fd;
            }
            i--;
            nfds--;
            }
        }
        }

    } while (end_server == FALSE); /* End of serving running.    */

/*************************************************************/
/* Clean up all of the sockets that are open                 */
/*************************************************************/
    for (i = 0; i < nfds; i++)
    {
        if(fds[i].fd >= 0)
        close(fds[i].fd);
    }

//         struct sockaddr_in addrClient;
//         socklen_t csize = sizeof(addrClient);

// /*-----------ACCEPTING CONNECTION-----------*/

//     _users[_nbUsers] = accept(_serverSocket, (struct sockaddr *) & addrClient, &csize);
//     if (_users[_nbUsers] > 0){
//         std::cout << "[+] Connection accepted with client fd nb " << _users[_nbUsers] << std::endl;
//     }
//     else
//         std::cout << "[+] Error while accepting" << std::endl;
//     char msg[5];

// /*-----------RECIEVING MESSAGE-----------*/

//     int res = recv(_users[_nbUsers], msg, 5, 0);
//     if (res >= 0)
//         std::cout << "[+] Client message is '" << msg << "' with nb characters " << res << std::endl;
//     else
//         std::cout << "[+] Error while recieving" << std::endl;

// /*-----------CLOSING-----------*/

//     if (close(_users[_nbUsers]) == 0 && close(_serverSocket) == 0)
//         std::cout << "[+] All sockets closed" << std::endl;
//     else
//         std::cout << "[+] Error while closing" << std::endl;

//     _nbUsers++;
// // Ici FIN boucle

}

Server::~Server(void) {}
