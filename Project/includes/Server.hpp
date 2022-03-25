#ifndef SERVER_HPP
# define SERVER_HPP

# include <arpa/inet.h>
# include <cstring>
# include <errno.h>
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
# include <map>
# include "Client.hpp"

# define ERR_ARG -1
# define ERR_SOCKET -2
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2048
# endif

class Client;

class Server
{
	private:
		int					_port;
		std::string			_password;
		std::map<int, Client>	_clientList;

	public:
		Server();
		Server(Server const & src);
		Server(int port, std::string password);
		~Server();
		Server				&operator=( Server const & rhs );
		int					start(void);
		std::string			getPassword(void) const;
		int					getPort(void) const;
		std::map<int, Client> getClientList(void) const;
		Client				getClientFromInfo(int fd) const;
		Client				getClientFromInfo(std::string username) const;
		void				createClient(pollfd fd, char *buffer);
		void				removeClient(pollfd *tab, int i, int &size);


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