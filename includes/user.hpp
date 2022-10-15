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


		bool	isPassChecked() const;
		bool	isRegistered() const;
		bool	isOperator() const;

		std::string	getBuffer() const;

	private:
		User();
		User &operator=(const User &other);

		struct sockaddr_in	_clientAddr;
		std::string			_userName;
		std::string			_realName;
		std::string			_nickName;
		bool				_isPassChecked;
		bool				_isRegistered;
		bool				_isOperator;
		std::string			_hostName;
		int					_port;
		
	public:
		int					clientSocket;
		std::string			_buffer;
		std::vector<std::string> replies;

	public:
		void		setUsername(const std::string &username);
		void		setRealname(const std::string &username);
		void		setNickname(const std::string &nick);
		void		setPassChecked(void);
		void		setRegistered(void);
		void		setOperator(void);
		int		setHostName(int newFileDescriptor);
		void		setSocket(const int &socket);
		
		void		setHost();
		void		setPort();

		void		setBuffer(const std::string &buf);
		void		resetBuffer();

		bool		operator==(const User& y);

		void		addRepliesToBuffer(const std::string &message);
};

#endif
