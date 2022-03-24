#ifndef SERVER_HPP
# define SERVER_HPP

# include <arpa/inet.h>
# include <cstring>
# include <fcntl.h>
# include <iomanip>
# include <iostream>
# include <netdb.h>
# include <netinet/in.h>
# include <poll.h>
# include <signal.h>
# include <string>
# include <sys/socket.h>
# include <sys/types.h>
# include <time.h>
# include <unistd.h>
# include <vector>
# include "Client.hpp"

# define ERR_ARG -1
# define ERR_SOCKET -2

class Client;

class Server
{
	private:
		int					_port;
		std::string			_password;
		std::vector<Client>	_clientList;

	public:
		Server();
		Server(Server const & src);
		Server(int port, std::string password);
		~Server();
		Server				&operator=( Server const & rhs );
		int					start(void);
		std::string			getPassword(void) const;
		int					getPort(void) const;
		std::vector<Client> getClientList(void) const;
		Client				getClientFromInfo(int fd) const;
		Client				getClientFromInfo(std::string username) const;

//									EXCEPTIONS								  //
		class ClientNotFoundException : virtual public std::exception
		{
			public:
				ClientNotFoundException() {}
				virtual ~ClientNotFoundException() throw () {}
				const char *what() const throw() { return "❓ Can't find the client in DataBase ❓"; };
		};
};

std::ostream &			operator<<( std::ostream & o, Server const & i );

#endif /* ********************************************************** SERVER_H */