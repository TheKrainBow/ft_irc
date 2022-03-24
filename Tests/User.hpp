#ifndef USER_HPP
# define USER_HPP

# include <iostream>
# include <string>

class Channel;

typedef enum e_userMode
{
	I, S, W, O
}				t_userMode;

class User
{
	private:
		std::string	_username;
		Channel		*_channels;
		t_userMode	_mode;

	public:
		User();
		User( User const & src );
		~User();


		User &		operator=( User const & rhs );
		std::string	getUsername();
		void		setUsername(std::string username);
		std::string	*getListChannels(void);
		t_userMode	getMode(void);
		void		setMode(t_userMode mode);

};

std::ostream &			operator<<( std::ostream & o, User const & i );

#endif /* ************************************************************ USER_H */