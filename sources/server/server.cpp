#include "server.hpp"

/* ************************************************************************** */
/*                        CONSTRUCTORS / DESTRUCTORS                          */
/* ************************************************************************** */

Server::Server(int port, std::string password)
: _password(password), _operUsername("operator_power"),_operPassword("acc_power"), _port(port), _nfds(0), _end_server(false) {}

Server::~Server(void) {
    if (_serverSocket != -1)
        quitServer();
}

/* ************************************************************************** */
/*                         PUBLIC MEMBER FUNCTIONS                            */
/* ************************************************************************** */

std::string &Server::getPassword(void) {
    return _password;
}

std::string &Server::getOperUsername(void) {
    return _operUsername;
}

std::string &Server::getOperPassword(void) {
    return _operPassword;
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
    _initTime();
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
        ret = poll(_fds, _nfds, POLL_TIMEOUT);
        if (ret < 0)
            std::cerr << "[-] poll() failed" << std::endl;
        if (ret == 0)
            std::cerr << "[-] poll() timed out." << std::endl;
        if (ret <= 0)
            return;
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
    since they will inherit that state from the listening server socket.
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
    - make the server listen for incoming client connection
*******************************************************************************/
void    Server::_listen(void){
    int ret;
    ret = listen(_serverSocket, MAX_CONNECTS);
    if (ret == 0)
        std::cout << "[+] Server is listening" << std::endl;
    else
        std::cerr << "[-] listen() failed" << std::endl;
}

/******************************************************************************/
/*  _initFileDescriptorsStruct()
    - Initializes the pollfd structure _fds
    - Sets up the initial listening socket 
    - _fds[0].fd = server/listening socket
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
    determine whether it's the listening or the active connection.
*******************************************************************************/
void    Server::_handleEvents(void) {       
    int     i;
	int 	ret = 0;
    std::list<User>::iterator it = users.begin();
    std::list<User>::iterator temp;

    for (i = 0; i < _nfds; i++){
        if(_fds[i].revents == 0)
            continue;
    // verifier si c'est vraiment necessaire parce que ca bloque IRSSI
        if(_fds[i].revents != POLLIN){
            _end_server = true;
            break;
        }
        if (_fds[i].fd == _serverSocket)
            _serverSocketEvent();
        else {
            while (it != users.end()) {
                if (_fds[i].fd == (*it).clientSocket) {
                    (*it).newAction();
                    _clientSocketEvent(i, (*it));
                    break;
                }
                temp = it;
                it++;
                checkActivity(*temp);
            }
			for (it = users.begin(); it != users.end(); it++){
				if ((*it).replies.size())
        			ret = _sendMessage(*it);
				if (ret < 0)
					closeOneConnection((*it));
			}
        }
    }
}

void    Server::checkActivity(User &user) {
    long    now = getTime();
    long    timeSinceLastAction = now - user.getLastAction();

    if (timeSinceLastAction > MAX_IDLE_TIME)
        closeOneConnection(user);
    else if (timeSinceLastAction > TIME_TO_PING)
        user.addRepliesToBuffer(PING_message(user.getHostname()));
}



/******************************************************************************/
/*  _serverSocketEvent()
    - Handle serversocket (= listeningsocket) events, here :
        - connection of a new client
    - Accepts the connection
    - Make the client socket file descriptor non blocking (can make other
    actions while socket is waiting for an event)
    - Creates the new fd in the fd structure
    - Creates a new user
*******************************************************************************/
void    Server::_serverSocketEvent(void) {
    int newFileDescriptor = 0;

    while (newFileDescriptor != -1) {
        newFileDescriptor = _acceptNewConnections();
        if (newFileDescriptor < 0)
            break;
        if (_makeSocketNonBlocking(newFileDescriptor)) {
            _addtoStruct(newFileDescriptor);
            User newUser(newFileDescriptor);
            if (!newUser.setHostName(newFileDescriptor))
                _end_server = true;
            users.push_back(newUser);
        }
    }
}

int    Server::_acceptNewConnections(void) {
    int newFileDescriptor = 0;
    struct sockaddr_in clientaddr;
    socklen_t clientaddr_size = sizeof(clientaddr);

    newFileDescriptor = accept(_serverSocket, (struct sockaddr *)&clientaddr, &clientaddr_size);
    if (newFileDescriptor < 0) {
        if (errno != EWOULDBLOCK) {
            std::cerr << "[-] accept() failed" << std::endl;
            _end_server = true;
        }
    }
    else
        std::cout << "[+] New incoming connection - " << newFileDescriptor << std::endl;
    return newFileDescriptor;
}

bool    Server::_makeSocketNonBlocking(int newFileDescriptor) {
    if (fcntl(newFileDescriptor, F_SETFL, O_NONBLOCK) < 0){
        std::cerr << "[-] fcntl() failed" << std::endl;
        close(newFileDescriptor);
        return false;
    }
    return true;
}

/******************************************************************************/
/*  _clientSocketEvent()
    - Handle _clientSocket events:
        - receives messages
        - if no error, processes the command
        - if the client fd still exists(= command was not quit or die or did 
        not succeed), checks if server needs to send messages
        - send messages
*******************************************************************************/
void    Server::_clientSocketEvent(int i, User &user) {
    char    buffer[MAX_BUFFER];
    int     ret;
    bool    close_conn = false;
    int     client_fd = _fds[i].fd;

    while (close_conn == false && client_fd > 0)
    {
        if (_fds[i].revents == POLLIN) {
            memset(buffer, '\0', MAX_BUFFER);
            ret = recv(client_fd, buffer, sizeof(buffer), 0);
            if (ret < 0) {
                if (errno != EWOULDBLOCK) {
                    std::cerr << "[-] recv() failed" << errno << std::endl;
                    close_conn = true;
                }
                break;
            }
            else if (ret == 0)
                close_conn = true;
            if (close_conn == false) {
                _handleBuffer(buffer, user);
                if (client_fd != _fds[i].fd)
                    break;
            }
		}
    }
    if ((client_fd == _fds[i].fd) && close_conn == true)
        closeOneConnection(user);
}

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
    std::cout << "[+] connection closed " << std::endl;
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
/*  quitServer()
    - closes all the connections
    - closes the server
    - sends a message explaining why
*******************************************************************************/
void    Server::quitServer(void) {
    std::list<User>::iterator it = users.begin();
    std::list<User>::iterator ite = users.end();
    std::list<User>::iterator temp;
    int serverSocket = _fds[0].fd;

    while (it != ite) {
        temp = it;
        it++;
        closeOneConnection(*temp);
    }
    _fds[0].fd = -1;
    _serverSocket = -1;
    // if (serverSocket>0)
        close(serverSocket);
    _end_server = true;
    return;
}


/******************************************************************************/
/*  quitMessage()
    to all users : "<nickmask> QUIT <reason>"
    This is the nickmask of the person who leave
*******************************************************************************/
void    Server::quitMessage(std::string &leaver, std::string &reason) {
    std::list<User>::iterator it = users.begin();
    std::list<User>::iterator ite = users.end();

    for(;it != ite;it++)
        it->addRepliesToBuffer(QUIT_message(leaver, reason));
}

void    Server::nickMessage(const std::string &prefix, std::string &nick) {
    std::list<User>::iterator it = users.begin();
    std::list<User>::iterator ite = users.end();

    for(;it != ite;it++)
        it->addRepliesToBuffer(NICK_message(prefix, nick));
}

std::string 			    &Server::getPrefix() {return _command.prefix; }
std::string				    &Server::getCommand() {return _command.cmd_name; }
std::vector<std::string>	&Server::getArgs() {return _command.args; }
std::string				    &Server::getTrailer() {return _command.trailer; }
