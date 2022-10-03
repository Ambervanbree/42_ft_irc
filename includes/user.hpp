#ifndef USER_HPP
# define USER_HPP
# include <string>
# include <vector>
# include <algorithm>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <iostream>
# include "server.hpp"

class Server;

class User
{
	public:
		User(Server &s, const int &socket, const std::string &user,
			const std::string &nick);
		~User();

		std::string			getPass() const;
		std::string			getUsername() const;
		std::string			getNickname() const;
		// struct sockaddr_in	getAddr() const;
		int					getSocket() const;
		std::string			getHost() const;
		int					getPort() const;
		std::string			getPrefix() const;

	private:
		User();
		User(const User &other);
		User &operator=(const User &other);

		Server*				_server;
		int					_clientSocket;
		// struct sockaddr_in	_clientAddr;
		std::string			_userName;
		std::string			_nickName;
		std::string			_hostName;
		int					_port;

	public:
		void		_setPass(const std::string &pass);
		void		_setUsername(const std::string &username);
		void		_setNickname(const std::string &nick);
		// void		_setAddr(const struct sockaddr_in &addr);
		void		_setSocket(const int &socket);
		void		_setHost();
		void		_setPort();
};

#endif