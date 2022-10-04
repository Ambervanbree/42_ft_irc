#include "user.hpp"

User::User(Server &s, const int &socket)
	: _server(&s), clientSocket(socket)
{
	std::cout << "[+] A user is born" << std::endl;
	// _setPass(user);
	_setUsername("dflt user");
	_setNickname("dflt nick");
	// _setHost();
	// _setPort();
}

User::~User() {};

// User::User() : _nickName("default user") { std::cout << "A user is born\n"; }


User::User(const User &other)
{
	if (this != &other)
	{
		_server = other._server;
		clientSocket = other.clientSocket;
		_userName = other._userName;
		_nickName = other._nickName;
		_hostName = other._hostName;
		_port = other._port;
	}
}

/*Public member functions*/

/*Getters*/
std::string			User::getUsername()	const { return _userName; }
std::string 		User::getNickname() const { return _nickName; }
// struct sockaddr_in	User::getAddr() const { return _clientAddr; }
int					User::getSocket() const { return clientSocket; }
std::string			User::getHost() const { return _hostName; }
std::string			User::getNickMask() const { return (getNickname() + "!" + getUsername() + "@" + getHost()); }
std::string			User::getPrefix() const
{
	std::string prefix;
	prefix = ":" + getNickname() + "!" + getUsername() + "@" + getHost();
	return prefix;
}

/*Setters*/
void				User::_setUsername(const std::string &user) { _userName = user; }
void				User::_setNickname(const std::string &nick) {
	if (nick.length() > 9){
		std::cerr << "(432) ERR_ERRONEUSNICKNAME" << std::endl;
		return;
	}
	std::list<User>::iterator ite;
	for(ite = _server->users.begin(); ite != _server->users.end(); ite++){
		if ((*ite).getNickname().compare(nick) == 0){
			std::cerr << "(433) ERR_NICKNAMEINUSE" << std::endl;
			return;
		}
	}
	_nickName = nick;
}
// void				User::_setAddr(const struct sockaddr_in &addr) { _clientAddr = addr; }
void				User::_setSocket(const int &socket) { clientSocket = socket; }

/*Private member functions*/

// void				User::_setHost() { _hostName = inet_ntoa(_clientAddr.sin_addr); }
// void				User::_setPort() { _port = ntohs(_clientAddr.sin_port); }


