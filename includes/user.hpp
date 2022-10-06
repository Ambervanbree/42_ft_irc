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

#define USERLEN 18

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

		void	setPassChecked(void);
		// void	setNickRegistered(const bool nickRegister);
		// void	setUserRegistered(const bool userRegister);
		void	setRegistered(void);

		bool	getPassChecked() const;
		// bool	getNickRegistered() const;
		// bool	getUserRegistered() const;
		bool	getRegistered() const;

		void	setBuffer(const std::string &buf);
		void	resetBuffer();
		std::string	getBuffer() const;
	
	private:
		User();
		User &operator=(const User &other);

		struct sockaddr_in	_clientAddr;
		std::string			_userName;
		std::string			_realName;
		std::string			_nickName;
		bool				_isPassChecked;
		// bool				_isNickRegistered;
		// bool				_isUserRegistered;
		bool				_isRegistered;
		std::string			_hostName;
		int					_port;
		
	public:
		int					clientSocket;

	public:
		void		setUsername(const std::string &username);
		void		setRealname(const std::string &username);
		void		setNickname(const std::string &nick);
		void		setAddr(const struct sockaddr_in &addr);
		void		setSocket(const int &socket);
		
		std::string			_buffer;


		void		setHost();
		void		setPort();
		// void		_initRegister();

		bool		operator==(const User& y);
};

#endif
