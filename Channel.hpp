#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <string>

class User;

typedef struct s_user
{
	User		user;
	std::string	nickname;
}				t_user;

class Channel
{

	public:

		Channel();
		Channel( Channel const & src );
		~Channel();

		Channel &		operator=( Channel const & rhs );

		std::string	getNickname();
		void		setNickname(std::string nickname1, std::string nickname2, std::string nickname3);
		

	private:
		std::string	_name;
		t_user		*_admins;
		t_user		*_operators;
		t_user		*_users;
		User		*_banned;
		bool		_inviteOnly;

};

std::ostream &			operator<<( std::ostream & o, Channel const & i );

#endif /* ********************************************************* CHANNEL_H */