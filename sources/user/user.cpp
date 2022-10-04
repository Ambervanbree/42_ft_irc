#include "user.hpp"

User::User(const int &socket)
	:clientSocket(socket) {
	std::cout << "[+] A user is born" << std::endl;
	_setUsername("dflt user");
	_setNickname("dflt nick");
	// _setHost();
	// _setPort();
}

User::~User() {};

// User::User() : _nickName("default user") { std::cout << "A user is born\n"; }


User::User(const User &other)
{
	if (this != &other) {
		clientSocket = other.clientSocket;
		_userName = other._userName;
		_nickName = other._nickName;
		_hostName = other._hostName;
		_port = other._port;
		_clientAddr = other._clientAddr;
		_isPassRegistered = other._isPassRegistered;
		_isNickRegistered = other._isNickRegistered;
		_isUserRegistered = other._isUserRegistered;
		_isRegistered = other._isRegistered;
	}
}

/*Public member functions*/

/*Getters*/
std::string			User::getUsername()	const { return _userName; }
std::string 		User::getNickname() const { return _nickName; }
struct sockaddr_in	User::getAddr() const { return _clientAddr; }
int					User::getSocket() const { return clientSocket; }
std::string			User::getHost() const { return _hostName; }
std::string			User::getNickMask() const { return (getNickname() + "!" + getUsername() + "@" + getHost()); }
std::string			User::getPrefix() const
{
	std::string prefix;
	prefix = ":" + getNickname() + "!" + getUsername() + "@" + getHost();
	return prefix;
}

bool	User::getPassRegistered() const { return _isPassRegistered; }
bool	User::getNickRegistered() const { return _isNickRegistered; }
bool	User::getUserRegistered() const { return _isUserRegistered; }
bool	User::getRegistered() const { return _isRegistered; }

/*Setters*/
void				User::_setNickname(const std::string &nick) { _nickName = nick; }
void				User::_setUsername(const std::string &user) { _userName = user; }
void				User::_setRealname(const std::string &realname) { _realName =  realname; }
void				User::_setAddr(const struct sockaddr_in &addr) { _clientAddr = addr; }
void				User::_setSocket(const int &socket) { clientSocket = socket; }

void	User::setPassRegistered(const bool passRegister) { _isPassRegistered = passRegister; }
void	User::setNickRegistered(const bool nickRegister) { _isNickRegistered = nickRegister; }
void	User::setUserRegistered(const bool userRegister) { _isUserRegistered = userRegister; }
void	User::setRegistered(const bool isregister) { _isRegistered = isregister; }

void	User::_initRegister()
{	
	_isPassRegistered = false;
	_isNickRegistered = false;
	_isUserRegistered = false;
	_isRegistered = false;
}

void				User::_setHost() { _hostName = inet_ntoa(_clientAddr.sin_addr); }
void				User::_setPort() { _port = ntohs(_clientAddr.sin_port); }


/*Handling buffer*/

void		User::setBuffer(const std::string &buf) { std::string tmp = _buffer + buf; _buffer = tmp; }
void		User::resetBuffer() { _buffer.clear(); }
std::string	User::getBuffer() const { return _buffer; }
