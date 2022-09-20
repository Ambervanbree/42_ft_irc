#ifndef USER_HPP
# define USER_HPP
# include <string>
# include <netinet/in.h>

class User
{
	public:
		User(const std::string &user, const std::string &nick);
		~User();

		void		setUsername(const std::string &user);
		std::string	getUsername() const;
		void		setNickname(const std::string &nick);
		std::string	getNickname() const;
		void		setAddr(const struct sockaddr_in &addr);
		struct sockaddr_in	getAddr() const;
		void		setSocket(const int &socket);
		int			getSocket() const;

	private:
		User();
		User(const User &other);
		User &operator=(const User &other);

		int					_clientSocket;
		struct sockaddr_in	_clientAddr;
		std::string			_userName;
		std::string			_nickName;
};

#endif