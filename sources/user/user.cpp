#include "user.hpp"

User::User(const int &socket, const struct sockaddr_in &addr, const std::string &user,
	const std::string &nick)
	: _clientSocket(socket), _clientAddr(addr)  , _userName(user), _nickName(nick)
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
		_hostName = other._hostName;
		_port = other._port;
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

std::string			User::getPrefix() const
{
	std::string prefix;
	prefix = ":" + getNickname() + "!" + getUsername() + "@" + getHost();
	return prefix;
}

/*Setters*/
void				User::setUsername(const std::string &user) { _userName = user; }
void				User::setNickname(const std::string &nick) { _nickName = nick;}
void				User::setAddr(const struct sockaddr_in &addr) { _clientAddr = addr; }
void				User::setSocket(const int &socket) { _clientSocket = socket; }

/*Private member functions*/

void				User::_setHost() { _hostName = inet_ntoa(_clientAddr.sin_addr); }
void				User::_setPort() { _port = ntohs(_clientAddr.sin_port); }

