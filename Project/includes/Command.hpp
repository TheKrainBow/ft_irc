#ifndef COMMAND_HPP
# define COMMAND_HPP

# include <iostream>
# include <string>
# include "Client.hpp"

class Command
{
	private:
		std::string	_command;
		std::string	*_arguments;
		int			_len;
		Client		&_client;

	public:
		Command(std::string command, std::string *args, int len, Client &Client);
		Command( Command const & src );
		~Command();
		Command &operator=( Command const & rhs );
		std::string	getCommand(void) const;
		void		nick(void);
		void		user(void);
		void		cap(void);
};

std::ostream &			operator<<( std::ostream & o, Command const & i );

#endif /* ********************************************************* COMMAND_H */