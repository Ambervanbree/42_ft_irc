#ifndef USER_HPP
# define USER_HPP

# include <string>
# include <vector>
# include <algorithm>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <iostream>
# include <list>
# include "server.hpp"

class Server;

class User
{
	public:
		User(const int &socket);
		User(const User &other);
		~User();

		std::string			getPass() const;
		std::string			getUsername() const;
		std::string			getNickname() const;
		struct sockaddr_in	getAddr() const;
		int					getSocket() const;
		std::string			getHost() const;
		int					getPort() const;
		std::string			getPrefix() const;
		std::string			getNickMask() const;

		void	setPassRegistered(const bool passRegister);
		void	setNickRegistered(const bool nickRegister);
		void	setUserRegistered(const bool userRegister);
		void	setRegistered(const bool setRegister);

		bool	getPassRegistered() const;
		bool	getNickRegistered() const;
		bool	getUserRegistered() const;
		bool	getRegistered() const;

		void	setBuffer(const std::string &buf);
		void	resetBuffer();
		std::string	getBuffer() const;
	
	private:
		User();
		User &operator=(const User &other);

		struct sockaddr_in	_clientAddr;
		std::string			_userName;
		std::string			_nickName;
		std::string			_hostName;
		int					_port;
		
	public:
		int					clientSocket;

	public:
		void		_setUsername(const std::string &username);
		void		_setNickname(const std::string &nick);
		void		_setAddr(const struct sockaddr_in &addr);
		void		_setSocket(const int &socket);
		
		std::string			_buffer;

		bool	_isPassRegistered;
		bool	_isNickRegistered;
		bool	_isUserRegistered;
		bool	_isRegistered;

		void		_setHost();
		void		_setPort();
		void		_initRegister();
};

#endif
