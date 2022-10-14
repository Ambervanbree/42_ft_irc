#include "server.hpp"

/* ************************************************************************** */
/*                        CONSTRUCTORS / DESTRUCTORS                          */
/* ************************************************************************** */

Server::Server(int port, std::string password)
: _password(password), _port(port), _nfds(0), _end_server(false) {}

Server::~Server(void) {
    _quitServer();
}

/* ************************************************************************** */
/*                         PUBLIC MEMBER FUNCTIONS                            */
/* ************************************************************************** */

std::string &Server::getPassword(void) {
    return _password;
}

/******************************************************************************/
/*  start()
    - Initializes commands
    - Creates server socket
    - Binds the server socket
    - Makes it listen
    - Initilizes the file descriptors structure

*******************************************************************************/
void    Server::start(void){
	_setCommands();
    _makeServerSocket();
    _bind();
    _listen();
    _initFileDescriptorsStruct();
}

/******************************************************************************/
/*  handleConnections()
    - Loop waiting for incoming connects (for server socket) or for incoming 
    data on any of the connected sockets.
    - Call poll() and wait TIME_OUT for it to complete.
    - Check to see if the poll call failed.
    - Check to see if the TIME_OUT expired.

*******************************************************************************/
void   Server::handleConnections(void){
    int     ret;

    while (_end_server == false) {
        ret = poll(_fds, _nfds, TIME_OUT);
        if (ret < 0)
            std::cerr << "[-] poll() failed" << std::endl;
        if (ret == 0)
            std::cerr << "[-] poll() timed out." << std::endl;
        if ((ret < 0) || (ret == 0))
            _quitServer();
        _handleEvents();
    }
}

/* ************************************************************************** */
/*                         PRIVATE MEMBER FUNCTIONS                           */
/* ************************************************************************** */

/******************************************************************************/
/*  _makeServerSocket()
    - socket() function creates the server socket that will recieve incoming
    connections
    - setsockopt() function allows the server socket to be reusable (so_reuseaddr
    poption)
    - fcntl() function sets the server socket to be nonblocking. 
    All of the sockets for the incoming connections will also be nonblocking 
    since they will inherit that state from the _listen server socket.
*******************************************************************************/
void    Server::_makeServerSocket(void){
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
/*  _bind()
    - initializes the sockaddr_in structure (_serverAddr) with memset
    - binds an address that clients can use to find the server
*******************************************************************************/
void    Server::_bind(void){
    int ret;

    memset(&_serverAddr, 0, sizeof(_serverAddr));
    _serverAddr.sin_family = AF_INET;
    memcpy(&_serverAddr.sin_addr, &in6addr_any, sizeof(in6addr_any));
    _serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    _serverAddr.sin_port = htons(_port);
    ret = bind(_serverSocket, (const struct sockaddr *) &_serverAddr, sizeof(_serverAddr));
    if (ret < 0){
        std::cerr << "bind() failed" << std::endl;
        close(_serverSocket);
        exit(-1);
    }
}

/******************************************************************************/
/*  _listen()
    - make the server listen for incoming client connexion
*******************************************************************************/
void    Server::_listen(void){
    int ret;
    ret = listen(_serverSocket, MAX_CONNECTS);
    if (ret == 0)
        std::cout << "[+] Server is _listen" << std::endl;
    else
        std::cerr << "listen() failed" << std::endl;
}

/******************************************************************************/
/*  _initFileDescriptorsStruct()
    - Initializes the pollfd structure _fds
    - Sets up the initial _listen socket 
    - _fds[0].fd = server/_listen socket
    - _fds[0].events = events we are interested in managing
            POLLIN event = There is data to read
            POLLOUT event = Writing is now possible

    !!! We might have to add other events !!!
*******************************************************************************/
void    Server::_initFileDescriptorsStruct(void){
    _nfds = 0;
    memset(_fds, _nfds , sizeof(_fds));
    _addtoStruct(_serverSocket);
}

/******************************************************************************/
/*  _addtoStruct()
    - Initializes the pollfd structure _fds
    - Sets up the initial listening socket 
    - _fds[0].fd = server/listening socket
    - _fds[0].events = events we are interested in managing
            POLLIN event = There is data to read
            POLLOUT event = Writing is now possible

    !!! We might have to add other events !!!
*******************************************************************************/
void    Server::_addtoStruct(int fd) {
    _fds[_nfds].fd = fd;
    // _fds[_nfds].events = POLLIN | POLLOUT;
    _fds[_nfds].events = POLLIN;
    _fds[_nfds].revents = 0;
    _nfds++;
}


/******************************************************************************/
/*  _handleEvents()
    - Loop through to find the descriptors that returned POLLIN and 
    determine whether it's the _listen or the active connection.
*******************************************************************************/
void    Server::_handleEvents(void) {       
    int     i;
    std::list<User>::iterator it = users.begin();

    for (i = 0; i < _nfds; i++){
        if(_fds[i].revents == 0)
            continue;
    // verifier si c'est vraiment necessaire parce que ca bloque IRSSI
        if(_fds[i].revents != POLLIN){
            std::cout << "Error! revents = " << _fds[i].revents << std::endl;
            _end_server = true;
            break;
        }
        if (_fds[i].fd == _serverSocket)
            _serverSocketEvent();
        else {
            for(it = users.begin(); it != users.end(); it++){
                if (_fds[i].fd == (*it).clientSocket) {
                    _clientSocketEvent(i, (*it));
                    break;
                }
            }
        }
    }
}

/******************************************************************************/
/*  _serverSocketEvent()
    - Handle serversocket (= listeningsocket) events, here :
        - connection of a new client
    - Accepts the connexion
    - Make the client socket file descriptor non blocking (can make other
    actions while socket is waiting for an event)
    - Creates the new fd in the fd structure
    - Creates a new user
*******************************************************************************/
void    Server::_serverSocketEvent(void) {
    int new_fd = 0;

    while (new_fd != -1) {
        new_fd = accept(_serverSocket, NULL, NULL);
        if (new_fd < 0) {
            if (errno != EWOULDBLOCK) {
                std::cerr << "[-] accept() failed" << std::endl;
                _end_server = true;
            }
            break;
        }
        std::cout << "[+] New incoming connection - " << new_fd << std::endl;
        if (fcntl(new_fd, F_SETFL, O_NONBLOCK) < 0){
            std::cerr << "[-] fcntl() failed" << std::endl;
            close(new_fd);
        }
        _addtoStruct(new_fd);
        User newUser(new_fd);
        users.push_back(newUser);
    }
}

/******************************************************************************/
/*  _clientSocketEvent()
    - Handle _clientSocket events, here :
        - message reception
*******************************************************************************/
void    Server::_clientSocketEvent(int i, User &user) {
    char    buffer[MAX_BUFFER];
    int     ret;
    bool    close_conn = false;

    while (close_conn == false && _fds[i].fd > 0)
    {
        if (_fds[i].revents == POLLIN) {
            memset(buffer, '\0', MAX_BUFFER);
            ret = recv(_fds[i].fd, buffer, sizeof(buffer), 0);
            if (ret < 0) {
                if (errno != EWOULDBLOCK) {
                    std::cerr << "[-] recv() failed" << errno << std::endl;
                    close_conn = true;
                }
                break;
            }
            if (ret == 0)
                close_conn = true;
            if (close_conn == false)
                _handleBuffer(buffer, user);
            if (close_conn == false && user.replies.size())
            {
                ret = _sendMessage(user);
                if (ret < 0)
                     close_conn = true;
            }
        }
    }
    if (close_conn == true)
        closeOneConnection(user);
}

// /******************************************************************************/
// /*  sendMessage()
// *******************************************************************************/
// void 	Server::sendMessage(User &recipient, std::string message) {
// 	std::cout << "sending: " << message << std::endl;
// 	send(recipient.clientSocket, message.c_str(), message.size(), 0);
// }

/******************************************************************************/
/*  closeConnections()
    Closes client socket        
*******************************************************************************/
void    Server::closeOneConnection(User &user) {
    int i = 1;

    while(_fds[i].fd != user.clientSocket){
        i++;
	}
	partFromAllChannels(user, *this);
    users.remove(user);
    close(_fds[i].fd);
    _fds[i].fd = -1;
    _updateFdsStructure();
    // a supprimer :
    std::cout << "[+] Connection closed" << std::endl;
}

/******************************************************************************/
/*  _updateFdsStructure()
    Update the _fds array and decrement the number of file descriptors _nfds
*******************************************************************************/
void    Server::_updateFdsStructure(){
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
/*  _quitServer()
    - closes all the connexions
    - closes the server
    - sends a message explaining why
*******************************************************************************/
void    Server::_quitServer(void) {
    std::list<User>::iterator ite;
    int serverSocket = _fds[0].fd;

    for (ite = users.begin(); ite != users.end(); ite++)
        closeOneConnection(*ite);
    _fds[0].fd = -1;
    close(serverSocket);
    _end_server = true;
    return;
}

std::string 			    &Server::getPrefix() {return _command.prefix; }
std::string				    &Server::getCommand() {return _command.cmd_name; }
std::vector<std::string>	&Server::getArgs() {return _command.args; }
std::string				    &Server::getTrailer() {return _command.trailer; }
