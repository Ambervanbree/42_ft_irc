#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <iomanip>
# include <cstdlib>
# include <cstring>
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
# include <string>
# include <map>
# include <list>
# include "commands.hpp"
# include "channel.hpp"


// maximum length of the queue of pending connections
# define MAX_CONNECTS   5
// maximum number of connections
# define MAX_FDS        1024
// maximum command size
# define MAX_BUFFER     512
// timeout of 3 minutes (3 * 60 * 1000) miliseconds
# define TIME_OUT       180000

class Channel;

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
    int                 _timeout;
    int                 _nfds;
    struct  pollfd      _fds[MAX_FDS];
	
	std::map<std::string, command>	_commands;
	std::deque<std::string>			_bufferCommand;
  
  public:
    std::list<Channel>	_channels;
	std::list<User>		users;
    
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
    void listeningSocketEvent(bool *end_server);
    bool clientSocketEvent(int i);
    void acceptConnections(bool *end_server);
    
    void decrementFileDescriptors(void);
    void closeConnections(void);

	/*Functions to set command list and launch commands*/
	void _setCommands();
	std::deque<std::string> _splitMessage(std::string message);
	void _launchCommand(std::deque<std::string> command, User &user);
	void _splitBuffer(char *buffer);
	void _handleBuffer(char *buffer, int clientSocket);

public:
    void start(void);
    void handleConnections(void);

	void interpretCommand(std::string &message, User &user); /*Change to Private at the end of project*/
};

struct Command
{
	std::string				prefix;
	std::string 			cmd_name;
	std::deque<std::string>	args;
	std::string				trailer;
};

#endif