#include "Command.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Command::Command(std::string command, std::string *args, int len, Client &client) :
_command(command), _arguments(args), _len(len), _client(client) {}

Command::Command( const Command & src ) : _client(src._client)
{
	*this = src;
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Command::~Command()
{
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Command &				Command::operator=( Command const & rhs )
{
	_arguments = rhs._arguments;
	_command = rhs._command;
	_len = rhs._len;
	return *this;
}

std::ostream &			operator<<( std::ostream & o, Command const & i )
{
	o << i.getCommand();
	return o;
}


/*
** --------------------------------- METHODS ----------------------------------
*/

void	Command::nick()
{
	this->_client.SetNickname(_arguments[0]);
}

void	Command::user()
{
	this->_client.SetUsername(_arguments[0]);
}

void	Command::cap()
{
	if (_arguments[0].compare("LS") == 0)
	{
		// WAIT CAP END
	}
	else
	{
		// REGISTER USER
	}
}
/*
** --------------------------------- ACCESSOR ---------------------------------
*/

std::string			Command::getCommand(void) const
{
	return _command;
}


/* ************************************************************************** */