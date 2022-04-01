#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <string>
# include "../includes/Client.hpp"
# include "../includes/Server.hpp"

class Channel
{
	private:
		std::string				_name;
		std::vector<Client *>	_clients;
		Client*					_admin;
		Server*					_server;
		
	public:
		Channel();
		Channel( Channel const & src );
		~Channel();

		Client	*getAdmin(void);
		std::string	getName(void);
		Client	*getClient(std::string username);
		std::vector<Client *>	getClients(void);

		void	addClient(Client *newClient);



		Channel &		operator=( Channel const & rhs );


};

std::ostream &			operator<<( std::ostream & o, Channel const & i );

#endif /* ********************************************************* CHANNEL_H */