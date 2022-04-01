#include "../includes/Channel.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Channel::Channel()
{
}

Channel::Channel( const Channel & src )
{
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Channel::~Channel()
{
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Channel &				Channel::operator=( Channel const & rhs )
{
	//if ( this != &rhs )
	//{
		//this->_value = rhs.getValue();
	//}
	return *this;
}

std::ostream &			operator<<( std::ostream & o, Channel const & i )
{
	//o << "Value = " << i.getValue();
	return o;
}


/*
** --------------------------------- METHODS ----------------------------------
*/

Client	*Channel::getAdmin(void)
{
	return (_admin);
}

Client	*Channel::getClient(std::string username)
{
	for (std::vector<Client *>::iterator it = _clients.begin(); it != _clients.end(); it++)
	{
		if ((*it)->getUsername() == username)
			return *it;
	}
	return (nullptr);
}

std::vector<Client *>Channel::getClients(void)
{
	return (_clients);
}

void	Channel::addClient(Client *newClient)
{
	_clients.push_back(newClient);
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


/* ************************************************************************** */