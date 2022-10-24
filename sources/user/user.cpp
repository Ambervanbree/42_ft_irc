#include "user.hpp"

User::User(const int &socket)
	:_userName("dflt_user"), _realName("dflt_rname"), _nickName("dflt_nick"),
	_isPassChecked(false), _isRegistered(false), _isOperator(false),
	_signon(getTime()), _lastAction(_signon), clientSocket(socket) {
	std::cout << "[+] A user is born" << std::endl;
}

User::~User() {};

User::User(const User &other)
{
	if (this != &other) {
		clientSocket = other.clientSocket;
		_nickName = other._nickName;
		_userName = other._userName;
		_realName = other._realName;
		_hostName = other._hostName;
		_clientAddr = other._clientAddr;
		_isPassChecked = other._isPassChecked;
		_isRegistered = other._isRegistered;
		_isOperator = other._isOperator;
		_signon = other._signon;
		_lastAction = other._lastAction;
	}
}

/*Public member functions*/

/*Getters*/
std::string			User::getUsername()	const { return _userName; }
std::string 		User::getNickname() const { return _nickName; }
std::string			User::getRealname() const { return _realName; }
std::string			User::getHostname()	const { return _hostName; }
int					User::getSocket() const { return clientSocket; }
std::string			User::getNickMask() const { return (_nickName + "!" + _userName + "@" + _hostName); }

bool	User::isPassChecked() const { return _isPassChecked; }
bool	User::isRegistered() const { return _isRegistered; }
bool	User::isOperator() const { return _isOperator; }
long	User::getSignon() const {return _signon; }
long	User::getLastAction() const {return _lastAction; } ;
long	User::getIdle() const {return (_lastAction - _signon); }

/*Setters*/
void				User::setNickname(const std::string &nick) { _nickName = nick; std::cout << "[+] _nickName is now set to: " << _nickName << std::endl;}
void				User::setUsername(const std::string &user) { _userName = user; std::cout << "[+] _userName is now set to: " << _userName << std::endl;}
void				User::setRealname(const std::string &realname) { _realName =  realname; std::cout << "[+] _realName is now set to: " << _realName << std::endl;}
int 				User::setHostName(int newFileDescriptor) {
    memset(&_clientAddr, 0, sizeof(_clientAddr));
	socklen_t addr_size = sizeof(struct sockaddr_in);

    int ret = getpeername(newFileDescriptor, (struct sockaddr *)&_clientAddr, &addr_size);
	if (ret < 0){
        std::cerr << "getpeername() failed: " << std::strerror(errno) << std::endl;
        return 0;
    }
    char hostName[63];
    strcpy(hostName, inet_ntoa(_clientAddr.sin_addr));
	_hostName = (std::string)hostName;
	return 1;
}
void	User::setSocket(const int &socket) { clientSocket = socket; }
void	User::newAction(void) {_lastAction = getTime(); }

void	User::setPassChecked(void) { _isPassChecked = true; std::cout << "[+] pass successfully checked" << std::endl;}
void	User::setRegistered(void) { _isRegistered = true; }
void	User::setOperator(void) { _isOperator = true; std::cout << "[+] _Operator is now set to true" << std::endl;}

/*Handling buffer*/

void		User::setBuffer(const std::string &buf) { std::string tmp = _buffer + buf; _buffer = tmp; }
void		User::resetBuffer() { _buffer.clear(); }
std::string	User::getBuffer() const { return _buffer; }

bool		User::operator==(const User& y) {
	if ((clientSocket == y.clientSocket) && !_userName.compare(y._userName) && !_realName.compare(y._realName)
		&& !_nickName.compare(y._nickName))
			return 1;
	else
		return 0;
}

/*Replies*/

void User::addRepliesToBuffer(const std::string &message)
{
	size_t len;

	len = message.size();
	if (len < 2 || message[len - 1] != '\n' || message[len - 2] != '\r')
		return ;
	replies.push_back(message);
}
