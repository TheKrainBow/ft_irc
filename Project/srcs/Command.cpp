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


/*
** --------------------------------- ACCESSOR ---------------------------------
*/

std::string			Command::getCommand(void) const
{
	return _command;
}


/* ************************************************************************** */