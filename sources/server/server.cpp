#include "server.hpp"

/* ************************************************************************** */
/*                        CONSTRUCTORS / DESTRUCTORS                          */
/* ************************************************************************** */

Server::Server(int port, std::string password)
: _password(password), _port(port), _nfds(0) {}

Server::~Server(void) {
    closeAllConnections();
}

/* ************************************************************************** */
/*                         PUBLIC MEMBER FUNCTIONS                            */
/* ************************************************************************** */

std::string &Server::getPassword(void) {
    return _password;
}

void    Server::start(void){
	_setCommands();
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
    - setsockopt() function allows the server socket to be reusable (so_reuseaddr
    poption)
    - fcntl() function sets the server socket to be nonblocking. 
    All of the sockets for the incoming connections will also be nonblocking 
    since they will inherit that state from the listening server socket.
*******************************************************************************/
void    Server::makeServerSocket(void){
    int ret;
    int on = 1;

    _serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (_serverSocket < 0) {
        std::cerr << "[-] socket() failed" << std::endl;
        exit(-1);
    }
    ret = setsockopt(_serverSocket, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));
    // ---> A ESSAYER pour simplification
    // ret = setsockopt(_serverSocket, SOL_SOCKET, SO_REUSEADDR, on, sizeof(on));
    if (ret < 0){
        std::cerr << "[-] setsockopt() failed" << std::endl;
        close(_serverSocket);
        exit(-1);
    }
    ret = fcntl(_serverSocket, F_SETFL, O_NONBLOCK);
    if (ret < 0){
        std::cerr << "[-] fcntl() failed" << std::endl;
        close(_serverSocket);
        exit(-1);
    }
}

/******************************************************************************/
/*  binding()
    - initializes the sockaddr_in structure (_serverAddr) with memset
    - binds an address that clients can use to find the server
*******************************************************************************/
void    Server::binding(void){
    int ret;

    memset(&_serverAddr, 0, sizeof(_serverAddr));
    _serverAddr.sin_family = AF_INET;
    memcpy(&_serverAddr.sin_addr, &in6addr_any, sizeof(in6addr_any));
    _serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    _serverAddr.sin_port = htons(_port);
    ret = bind(_serverSocket, (const struct sockaddr *) &_serverAddr, sizeof(_serverAddr));
    // std::cout << "[+] The server socket has fd nb " << _serverSocket << std::endl;
    if (ret < 0){
        std::cerr << "bind() failed" << std::endl;
        close(_serverSocket);
        exit(-1);
    }
}

/******************************************************************************/
/*  listening()
    - make the server listen for incoming client connexion
*******************************************************************************/
void    Server::listening(void){
    int ret;
    ret = listen(_serverSocket, MAX_CONNECTS);
    if (ret == 0)
        std::cout << "[+] Server is listening" << std::endl;
    else
        std::cerr << "listen() failed" << std::endl;
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
    // _fds[_nfds].events = POLLIN | POLLOUT;
    _fds[_nfds].events = POLLIN;
    _fds[_nfds].revents = 0;
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

    while (end_server == false) {
        // std::cout << "[+] Waiting on poll()..." << std::endl;
        ret = poll(_fds, _nfds, TIME_OUT);
        // voir si pas plus logique ainsi:
        // ret = poll(_fds, MAX_FDS, TIME_OUT);
        if (ret < 0)
            std::cerr << "[-] poll() failed" << std::endl;
        if (ret == 0)
            std::cout << "[-] poll() timed out." << std::endl;
        if ((ret < 0) || (ret == 0)) {
            closeAllConnections();
            return;
        }
        handleEvents(&end_server);
    }
}

/******************************************************************************/
/*  handleEvents()
    - Loop through to find the descriptors that returned POLLIN and 
    determine whether it's the listening or the active connection.
*******************************************************************************/
void    Server::handleEvents(bool *end_server) {       
    int     i;
    std::list<User>::iterator it = users.begin();

    for (i = 0; i < _nfds; i++){
        if(_fds[i].revents == 0)
            continue;
    // verifier si c'est vraiment necessaire parce que ca bloque IRSSI
        // if((_fds[i].revents != POLLIN) && (_fds[i].revents != POLLOUT)){
        //     std::cout << "Error! revents = " << _fds[i].revents << std::endl;
        //     *end_server = true;
        //     break;
        // }
        if (_fds[i].fd == _serverSocket)
            listeningSocketEvent(end_server);
        else {
            for(it = users.begin(); it != users.end(); it++){
                if (_fds[i].fd == (*it).clientSocket) {
                    clientSocketEvent(i, (*it));
                    break;
                }
            }
        }
    }
}

void    Server::listeningSocketEvent(bool *end_server) {
    acceptConnections(end_server);
    // others;
}

void    Server::acceptConnections(bool *end_server) {
    int new_fd = 0;
    int ret = 0;

    // std::cout << "[+] Listening socket is readable" << std::endl;
    while (new_fd != -1) {
        new_fd = accept(_serverSocket, NULL, NULL);
        if (new_fd < 0) {
            if (errno != EWOULDBLOCK) {
                std::cerr << "[-] accept() failed" << std::endl;
                *end_server = true;
            }
            break;
        }
        std::cout << "[+] New incoming connection - " << new_fd << std::endl;
        ret = fcntl(new_fd, F_SETFL, O_NONBLOCK);
        if (ret < 0){
            std::cerr << "[-] fcntl() failed" << std::endl;
            close(new_fd);
            exit(-1);
        }
        _fds[_nfds].fd = new_fd;
        _fds[_nfds].events = POLLIN;
        // _fds[_nfds].events = POLLIN | POLLOUT;
        _fds[_nfds].revents = 0;
        _nfds++;
        User newUser(new_fd);
        users.push_back(newUser);
    }
}

void    Server::clientSocketEvent(int i, User &user) {
    bool    close_conn;
    char    buffer[MAX_BUFFER];
    int     ret;
    // char    resp[60] = "[+] J'ai bien recu ton message et je t'en remercie\n";
    
    // std::cout << "[+] Descriptor " << _fds[i].fd << " is readable" << std::endl;
    close_conn = false;

    while (_fds[i].fd > 0) {
        // if (_fds[i].revents == POLLOUT) {
            memset(buffer, '\0', MAX_BUFFER);
            ret = recv(_fds[i].fd, buffer, sizeof(buffer), 0);
            if (ret < 0) {
                if (errno != EWOULDBLOCK) {
                    std::cerr << "[-] recv() failed" << errno << std::endl;
                    close_conn = true;
                }
                break;
            }
            if (ret == 0) {
                std::cout << "[+] Connection closed" << std::endl;
                close_conn = true;
                break;
            }
            // ret = send(_fds[i].fd, resp, strlen(resp), 0);
            // if (ret < 0) {
            //     std::cerr << "[-] send() failed" << std::endl;
            //     close_conn = true;
            //     break;
            // }
            // std::cout << "[+] Message was sent" << std::endl;
            _handleBuffer(buffer, user);
        // }
        // if (_fds[i].revents == POLLIN) {
        // }
    }
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

void    Server::closeOneConnection(User &user) {
    int i = 0;
    int fd = user.clientSocket;

    while(_fds[i].fd != user.clientSocket)
        i++;
    users.remove(user);
    close(fd);
    _fds[i].fd = -1;
    decrementFileDescriptors();
    std::cout << "[+] Connection closed" << std::endl;
    // if (_nfds == 1) {
    //     close(_fds[0].fd);
    //     _fds[0].fd = -1;
    //     _nfds--;
    // }
}

void    Server::closeAllConnections(void) {
    std::list<User>::iterator ite = users.begin();
    
    for (; ite != users.end(); ite++){
        closeOneConnection(*ite);
    }
}


std::string 			&Server::getPrefix() {return _command.prefix; }
std::string				&Server::getCommand() {return _command.cmd_name; }
std::deque<std::string>	&Server::getArgs() {return _command.args; }
std::string				&Server::getTrailer() {return _command.trailer; }