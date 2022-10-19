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
# include "replies.hpp"


// maximum length of the queue of pending connections
# define MAX_CONNECTS   5
// maximum number of connections
# define MAX_FDS        1024
// maximum command size
# define MAX_BUFFER     510
// timeout in milliseconds (600000 = 10 minutes)
# define POLL_TIMEOUT   600000
// time of inactivity before ping in seconds
# define TIME_TO_PING   60
// maximum time of inactivity in seconds
# define MAX_IDLE_TIME  300


class Channel;
class User;
class Server;
typedef     void (*command)(User &user, Server &server);

struct Command
{
	std::string				    prefix;
	std::string 			    cmd_name;
	std::vector<std::string>	args;
	std::string				    trailer;
};

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
    std::string         _password;
    std::string         _operPassword;
    int                 _port;
    int                 _serverSocket;
    struct sockaddr_in  _serverAddr;
    int                 _timeout;
    int                 _nfds;
    struct  pollfd      _fds[MAX_FDS];
    bool                _end_server;
	
	std::map<std::string, command>	_commands;
	std::vector<std::string>		_bufferCommand;
  
  public:
	Command								_command;
	std::map<std::string, Channel *>	_channels;
	std::list<User>						users;
    std::list<std::string>          	operators;
    
/* ************************************************************************** */
/*                              MEMBER FUNCTIONS                              */
/* ************************************************************************** */

private:
    void _makeServerSocket(void);
    void _bind(void);
    void _listen(void);
    void _initFileDescriptorsStruct(void);
    void _addtoStruct(int fd);
    void _handleEvents(void);
    int  _acceptNewConnections(void);
    bool _makeSocketNonBlocking(int newFileDescriptor);
    void _serverSocketEvent(void);
    void _clientSocketEvent(int i, User &user);
    

	/*Functions to set command list and launch commands*/
	void _setCommands(void);
	void _messageToCommandStruct(std::string message);
	void _clearCommandStruct(void);
	void _launchCommand(User &user);
	void _splitBuffer(std::string buffer);
	void _handleBuffer(char *buffer, User &user);
    void _updateFdsStructure(void);
    
    /*Functions to send a message to a client*/
    int _sendMessage(User &user);

public:
    void start(void);
    void handleConnections(void);
    void checkActivity(User &user);
    void pingUser(User &user);
    void closeOneConnection(User &user);
    void quitServer(void);

    void errorMessage(User &recipient, std::string reason);
    void quitMessage(std::string &leaver, std::string &reason);

	void interpretCommand(std::string &message, User &user); /*Change to Private at the end of project*/

    std::string				&getPassword(void);
    std::string             &getOperPassword(void);

	std::string 			&getPrefix(void);
	std::string				&getCommand(void);
	std::vector<std::string>	&getArgs(void);
	std::string				&getTrailer(void);

};

#endif