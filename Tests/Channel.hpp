#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <string>
# include "User.hpp"
# include <vector>

class User;

class Channel
{
	private:
		std::string			_name;
		std::vector<User>	_admins;
		std::vector<User>	_operators;
		std::vector<User>	_users;
		std::vector<User>	_banned;
		bool				_inviteOnly;

	public:
		Channel();
		Channel( Channel const & src );
		~Channel();
		Channel &		operator=( Channel const & rhs );
		std::string		getNickname();
};

std::ostream &			operator<<( std::ostream & o, Channel const & i );

#endif /* ********************************************************* CHANNEL_H */