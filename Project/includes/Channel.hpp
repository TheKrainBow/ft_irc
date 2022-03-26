#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <string>

class Channel
{
	private:
		std::string	_name;
	public:
		Channel();
		Channel( Channel const & src );
		~Channel();

		Channel &		operator=( Channel const & rhs );


};

std::ostream &			operator<<( std::ostream & o, Channel const & i );

#endif /* ********************************************************* CHANNEL_H */