#include "user.hpp"

User::User(const std::string &user, const std::string &nick)
	: _userName(user), _nickName(nick) {
		std::cout << "User created\n";
	}

User::~User() {};

User::User() {};

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

std::string			User::getUsername()	const { return _userName; }
void				User::setUsername(const std::string &name) { _userName = name; }
std::string 		User::getNickname() const { return _nickName; }
void				User::setNickname(const std::string &user) { _nickName = user; }
void				User::setAddr(const struct sockaddr_in &addr) { _clientAddr = addr; }
struct sockaddr_in	User::getAddr() const { return _clientAddr; }
void				User::setSocket(const int &socket) { _clientSocket = socket; }
int					User::getSocket() const { return _clientSocket; }