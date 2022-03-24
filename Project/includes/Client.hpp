#ifndef Client_HPP
# define Client_HPP

# include <iostream>
# include <string>
# include <poll.h>
# include "Server.hpp"

class Server;

class Client
{
	private:
		std::string	_nickname;
		std::string	_username;
		struct pollfd	_fd; //pour avoir le fd, il faut faire _fd.fd
		Server		&_server;

	public:
		Client( Client const & src );
		Client(struct pollfd fd, std::string nickname, std::string username, Server &server);
		Client(std::string connexionBuffer, Server &server);
		~Client();
		Client 		&operator=(Client const & rhs);
	
		void		confirmConnexion(void);			//COMFIRME LA CONNEXION AU CLIENT
		void		command(std::string command);	//EXECUTE UNE COMMANDE
		int			getFd(void) const;
		std::string	getNickname(void) const;
		std::string	getUsername(void) const;

//									EXCEPTIONS								  //
		class AlreadyUsedParametersException : virtual public std::exception
		{
			private:
				std::string error_message;
			public:
				AlreadyUsedParametersException(const std::string &msg) : error_message(msg) {}
				virtual ~AlreadyUsedParametersException() throw () {}
				const char *what() const throw() { return error_message.c_str(); };
		};
		class ErrorInCommandException : virtual public std::exception
		{
			private:
				std::string error_message;
			public:
				ErrorInCommandException(const std::string &msg) : error_message(msg) {}
				virtual ~ErrorInCommandException() throw () {}
				const char *what() const throw() { return error_message.c_str(); };
		};
};

std::ostream &			operator<<( std::ostream & o, Client const & i );

#endif /* ************************************************************ Client_H */