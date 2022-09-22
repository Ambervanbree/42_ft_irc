#include "user.hpp"

User::User(const int &socket, const struct sockaddr_in &addr, const std::string &user,
	const std::string &nick)
	: _clientSocket(socket), _clientAddr(addr)  , _userName(user), _nickName(nick), _channels(0)
{
	_setHost();
	_setPort();
}

User::~User() {};

User::User() : _nickName("default user") { std::cout << "A user is born\n"; }


User::User(const User &other)
{
	if (this != &other)
	{
		_userName = other._userName;
		_nickName = other._nickName;
		_clientAddr = other._clientAddr;
		_clientSocket = other._clientSocket;
	}
}

/*Public member functions*/

/*Getters*/
std::string			User::getUsername()	const { return _userName; }
std::string 		User::getNickname() const { return _nickName; }
struct sockaddr_in	User::getAddr() const { return _clientAddr; }
int					User::getSocket() const { return _clientSocket; }
std::string			User::getHost() const { return _hostName; }

/*Setters*/
void				User::setUsername(const std::string &name) { _userName = name; }
void				User::setNickname(const std::string &user) { _nickName = user; }
void				User::setAddr(const struct sockaddr_in &addr) { _clientAddr = addr; }
void				User::setSocket(const int &socket) { _clientSocket = socket; }

void				User::addChannel(const std::string &channel)
{
	if (find(_channels.begin(), _channels.end(), channel) == _channels.end())
		_channels.push_back(channel); 
}


std::vector<std::string>	User::getChannelsList() { return _channels; }

/*Private member functions*/

void				User::_setHost() { _hostName = inet_ntoa(_clientAddr.sin_addr); }
void				User::_setPort() { _port = ntohs(_clientAddr.sin_port); }
