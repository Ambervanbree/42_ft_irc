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
# include <netdb.h>
# include <fcntl.h>
# include <unistd.h>
# include <poll.h>
# include <vector>

class Server {

/* ************************************************************************** */
/*                        CONSTRUCTORS / DESTRUCTORS                          */
/* ************************************************************************** */

public:
    Server(int port, std::string password);
    ~Server(void);

// private:
    // Server(void);
    // Server(const Server &rhs);
    // Server &operator= (const Server &rhs);

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
    struct  pollfd      _fds[200];
    
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
    bool clientSocketRecieveOrSend(int i, bool *end_server);
    void decrementFileDescriptors(void);
    void closeConnections(void);

public:
    void start(void);
    void handleConnections(void);

};

#endif