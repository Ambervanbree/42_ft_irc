#include "user.hpp"

User::User(const int &socket)
	:_userName("dflt_user"), _realName("dflt_rname"), _nickName("dflt_nick"),
	_isPassChecked(false), _isRegistered(false), _isOperator(false),
	clientSocket(socket) {
	std::cout << "[+] A user is born" << std::endl;
	// _setHost();
	// _setPort();
}

User::~User() {};

// User::User() : _nickName("default user") { std::cout << "A user is born\n"; }


User::User(const User &other)
{
	if (this != &other) {
		clientSocket = other.clientSocket;
		_nickName = other._nickName;
		_userName = other._userName;
		_realName = other._realName;
		_hostName = other._hostName;
		_port = other._port;
		_clientAddr = other._clientAddr;
		_isPassChecked = other._isPassChecked;
		_isRegistered = other._isRegistered;
		_isOperator = other._isOperator;
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

bool	User::isPassChecked() const { return _isPassChecked; }
bool	User::isRegistered() const { return _isRegistered; }
bool	User::isOperator() const { return _isOperator; }

/*Setters*/
void				User::setNickname(const std::string &nick) { _nickName = nick; std::cout << "[+] _nickName is now set to: " << _nickName << std::endl;}
void				User::setUsername(const std::string &user) { _userName = user; std::cout << "[+] _userName is now set to: " << _userName << std::endl;}
void				User::setRealname(const std::string &realname) { _realName =  realname; std::cout << "[+] _realName is now set to: " << _realName << std::endl;}

void				User::setAddr(const struct sockaddr_in &addr) { _clientAddr = addr; }
void				User::setSocket(const int &socket) { clientSocket = socket; }

void	User::setPassChecked(void) { _isPassChecked = true; std::cout << "[+] pass successfully checked" << std::endl;}
void	User::setRegistered(void) { _isRegistered = true; }
void	User::setOperator(void) { _isOperator = true; std::cout << "[+] _Operator is now set to true" << std::endl;}

void				User::setHost() { _hostName = inet_ntoa(_clientAddr.sin_addr); }
void				User::setPort() { _port = ntohs(_clientAddr.sin_port); }


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
	std::string tmp;
	//size_t next = 0;
	//size_t last = 0;

	len = message.size();
	if (len < 2 || message[len - 1] != '\n' || message[len - 2] != '\r')
	{
		std::cerr << "-> Invalid format on replies - please check\n";
		return ;
	}
	replies.push_back(message);
	/*else if (message[len -1] == '\n')
	{
		while ((next = message.find("\r\n", last)) != std::string::npos)
		{
			tmp = message.substr(last, next - last + 2);
			last = next + 2;
			replies.push_back(tmp);
		}
		tmp = message.substr(last);
		replies.push_back(tmp);
	}*/
}
