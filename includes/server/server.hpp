#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <iomanip>
# include <cstdlib>
# include <string.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <sys/ioctl.h>
# include <arpa/inet.h>
# include <errno.h>
# include <stdio.h>
# include <netdb.h>
# include <fcntl.h>
# include <unistd.h>
# include <poll.h>
# include <vector>

// maximum length of the queue of pending connections
# define MAX_CONNECTS   5
// maximum number of connections
# define MAX_FDS        1024
// maximum command size
# define MAX_BUFFER     512
// timeout of 3 minutes (3 * 60 * 1000) miliseconds
# define TIME_OUT       180000


class Server {

/* ************************************************************************** */
/*                        CONSTRUCTORS / DESTRUCTORS                          */
/* ************************************************************************** */

public:
    Server(int port, std::string password);
    ~Server(void);

private:
    Server(void);
    Server(const Server &rhs);
    Server &operator= (const Server &rhs);

/* ************************************************************************** */
/*                              MEMBER VARIABLES                              */
/* ************************************************************************** */

private:
    int                 _port;
    std::string         _password;
    int                 _serverSocket;
    struct sockaddr_in  _serverAddr;
    std::vector<int>    _channels;
    int                 _timeout;
    int                 _nfds;
    struct  pollfd      _fds[MAX_FDS];
    
/* ************************************************************************** */
/*                              MEMBER FUNCTIONS                              */
/* ************************************************************************** */

private:
    void makeServerSocket(void);
    void binding(void);
    void listening(void);

    void initConnections(void);
    void handleIncomingConnections(void);
    bool handleEvents(bool *end_server);
    void listeningSocketAcceptConnections(bool *end_server);
    bool clientSocketRecieveOrSend(int i);
    
    void decrementFileDescriptors(void);
    void closeConnections(void);

public:
    void start(void);
    void handleConnections(void);

};

#endif