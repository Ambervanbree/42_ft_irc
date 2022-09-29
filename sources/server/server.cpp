#include "server.hpp"

/* ************************************************************************** */
/*                        CONSTRUCTORS / DESTRUCTORS                          */
/* ************************************************************************** */

Server::Server(int port, std::string password)
: _port(port), _password(password), _nfds(0)  {}

Server::~Server(void) {
    closeConnections();
}



/* ************************************************************************** */
/*                         PUBLIC MEMBER FUNCTIONS                            */
/* ************************************************************************** */

void    Server::start(void){
    makeServerSocket();
    binding();
    listening();
}

void    Server::handleConnections(void){
    initConnections();
    handleIncomingConnections();
}


/* ************************************************************************** */
/*                         PRIVATE MEMBER FUNCTIONS                           */
/* ************************************************************************** */

/******************************************************************************/
/*  makeServerSocket()
    - socket() function creates the server socket that will recieve incoming
    connections
    - setsockopt() function allows the server socket to be reusable
    - fcntl() function sets the server socket to be nonblocking. 
    All of the sockets for the incoming connections will also be nonblocking 
    since they will inherit that state from the listening server socket.
*******************************************************************************/
void    Server::makeServerSocket(void){
    int ret;
    int on = 1;

    _serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (_serverSocket < 0) {
        perror("socket() failed");
        exit(-1);
    }
    ret = setsockopt(_serverSocket, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));
    if (ret < 0){
        perror("setsockopt() failed");
        close(_serverSocket);
        exit(-1);
    }
    ret = fcntl(_serverSocket, F_SETFL, O_NONBLOCK);
    if (ret < 0){
        perror("fcntl() failed");
        close(_serverSocket);
        exit(-1);
    }
}

/******************************************************************************/
/*  binding()
    - initializes the sockaddr_in structure (_serverAddr) with memset
    - binds the socket
*******************************************************************************/
void    Server::binding(void){
    int ret;

    memset(&_serverAddr, 0, sizeof(_serverAddr));
    _serverAddr.sin_family = AF_INET;
    memcpy(&_serverAddr.sin_addr, &in6addr_any, sizeof(in6addr_any));
    _serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    _serverAddr.sin_port = htons(_port);
    ret = bind(_serverSocket, (const struct sockaddr *) &_serverAddr, sizeof(_serverAddr));
        std::cout << "[+] The server socket has fd nb " << _serverSocket << std::endl;
    if (ret < 0){
        perror("bind() failed");
        close(_serverSocket);
        exit(-1);
    }
}

/******************************************************************************/
/*  listening()
    - make the server listen
*******************************************************************************/
void    Server::listening(void){
    int ret;
    ret = listen(_serverSocket, MAX_CONNECTS);
    if (ret == 0)
        std::cout << "[+] Server is listening" << std::endl;
    else
        perror("listen() failed");
}

/******************************************************************************/
/*  initConnections()
    - Initializes the pollfd structure _fds
    - Sets up the initial listening socket 
    - _fds[0].fd = server/listening socket
    - _fds[0].events = events we are interested in managing
            POLLIN event = There is data to read
            POLLOUT event = Writing is now possible

    !!! We might have to add other events !!!
*******************************************************************************/
void    Server::initConnections(void){
    _nfds = 0;
    memset(_fds, _nfds , sizeof(_fds));
    _fds[_nfds].fd = _serverSocket;
    _fds[_nfds].events = POLLIN | POLLOUT;
    _nfds++;
}

/******************************************************************************/
/*  handleIncomingConnections()
    - Loop waiting for incoming connects (for server socket) or for incoming 
    data on any of the connected sockets.
    - Call poll() and wait TIME_OUT for it to complete.
    - Check to see if the poll call failed.
    - Check to see if the TIME_OUT expired.

*******************************************************************************/
void   Server::handleIncomingConnections(void){
    int     ret;
    bool    end_server = false;
    bool    compress_array = false;

    while (end_server == false) {
        std::cout << "[+] Waiting on poll()..." << std::endl;
        ret = poll(_fds, _nfds, TIME_OUT);
        if (ret < 0)
            perror("poll() failed");
        if (ret == 0)
            std::cout << "[-] poll() timed out." << std::endl;
        if ((ret < 0) || (ret == 0))
            break;
        compress_array = handleEvents(&end_server);
        if (compress_array) {
            decrementFileDescriptors();
            compress_array = false;
        }
    }
}

/******************************************************************************/
/*  handleEvents()
    - Loop through to find the descriptors that returned POLLIN and 
    determine whether it's the listening or the active connection.
*******************************************************************************/
bool    Server::handleEvents(bool *end_server){       
    int     i;
    int     current_size = 0;
    bool    compress_array = false;

    current_size = _nfds;
    for (i = 0; i < current_size; i++){
        if(_fds[i].revents == 0)
            continue;
        if(_fds[i].revents != POLLIN){
            std::cout << "Error! revents = " << _fds[i].revents << std::endl;
            *end_server = true;
            break;
        }
        if (_fds[i].fd == _serverSocket)
            listeningSocketEvent(end_server);
        else
            compress_array = clientSocketEvent(i);
    }
    return compress_array;
}

void    Server::listeningSocketEvent(bool *end_server) {
    acceptConnections(end_server);
}

void    Server::acceptConnections(bool *end_server) {
    int new_fd = 0;

    std::cout << "[+] Listening socket is readable" << std::endl;
    while (new_fd != -1) {
        new_fd = accept(_serverSocket, NULL, NULL);
        if (new_fd < 0){
            if (errno != EWOULDBLOCK){
                perror("accept() failed");
                *end_server = true;
            }
            break;
        }
        std::cout << "[+] New incoming connection - " << new_fd << std::endl;
        _fds[_nfds].fd = new_fd;
        _fds[_nfds].events = POLLIN;
        _nfds++;
    }
}

bool    Server::clientSocketEvent(int i) {
    bool    close_conn;
    char    buffer[MAX_BUFFER];
    int     ret;
    int     len;
    bool    compress_array = false;
    
    std::cout << "[+] Descriptor " << _fds[i].fd << " is readable" << std::endl;
    close_conn = false;
    while (true) {
        memset(buffer, 0, strlen(buffer));
        ret = recv(_fds[i].fd, buffer, sizeof(buffer), 0);
        if (ret < 0){
            if (errno != EWOULDBLOCK){
                perror("  recv() failed");
                close_conn = true;
            }
            break;
        }
        if (ret == 0){
            std::cout << "  Connection closed" << std::endl;
            close_conn = true;
            break;
        }
        len = ret;
        std::cout << "[+] " << len << " bytes received" << std::endl;
        std::cout <<"[+] message : " << buffer << std::endl;
        // ret = send(_fds[i].fd, buffer, len, 0);
        // if (ret < 0){
        //     perror("send() failed");
        //     close_conn = true;
        //     break;
        // }
    }
    if (close_conn){
        close(_fds[i].fd);
        _fds[i].fd = -1;
        compress_array = true;
    }
    return compress_array;
}

/******************************************************************************/
/*  decrementFileDescriptors()
    If the compress_array flag was turned on, we need to squeeze together
    the array and decrement the number of file descriptors. We do not need
    to move back the events and revents fields because the events will always
    be POLLIN in this case, and revents is output.          
*******************************************************************************/
void    Server::decrementFileDescriptors(){
    int i;
    int j;

    for (i = 0; i < _nfds; i++){
        if (_fds[i].fd == -1){
            for(j = i; j < _nfds; j++)
                _fds[j].fd = _fds[j+1].fd;
            i--;
            _nfds--;
        }
    }
}

/******************************************************************************/
/*  closeConnections()
    Close sockets        
*******************************************************************************/
void    Server::closeConnections(void) {
    int i;
    for (i = 0; i < _nfds; i++){
        if(_fds[i].fd >= 0)
            close(_fds[i].fd);
    }
}
