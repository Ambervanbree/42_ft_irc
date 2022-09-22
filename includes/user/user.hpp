#ifndef USER_HPP
# define USER_HPP
# include <string>
# include <vector>
# include <algorithm>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <iostream>

class User
{
	public:
		User();

		User(const User &other);
		User(const int &socket, const struct sockaddr_in &addr, 
			const std::string &user, const std::string &nick);
		~User();

		void		setUsername(const std::string &user);
		void		setNickname(const std::string &nick);
		void		setAddr(const struct sockaddr_in &addr);
		void		setSocket(const int &socket);

		std::string			getUsername() const;
		std::string			getNickname() const;
		struct sockaddr_in	getAddr() const;
		int					getSocket() const;
		std::string			getHost() const;
		int					getPort() const;

		void						addChannel(const std::string &channel);
		std::vector<std::string>	getChannelsList();

	private:
		User &operator=(const User &other);

		int					_clientSocket;
		struct sockaddr_in	_clientAddr;
		std::string			_userName;
		std::string			_nickName;
		std::string			_hostName;
		int					_port;

		std::vector<std::string> _channels;

		void		_setHost();
		void		_setPort();

};

#endif