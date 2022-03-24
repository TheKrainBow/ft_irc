#include "Server.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Server::Server() {
	_port = -1;
	_password = std::string(NULL);
}

Server::Server( const Server & src ) {
	*this = src;
}

Server::Server(int port, std::string password) : _port(port), _password(password) {}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Server::~Server()
{
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Server &				Server::operator=( Server const & rhs )
{
	this->_password = rhs._password;
	this->_port = rhs._port;
	return *this;
}

std::ostream &			operator<<( std::ostream & o, Server const & i )
{
	o << "Server@" << i.getPassword() << ":" << i.getPort();
	return o;
}


/*
** --------------------------------- METHODS ----------------------------------
*/

void	Server::start(void)
{
//						LIGNES POUR SUPPRIMER LES ERREURS:					  //
	int fd = 0;
	std::string nick = "Toto";
	std::string name = "Tata";

//							 GESTION DES CONNEXIONS ICI					 	  //
//																			  //
//																			  //

//					LIGNES A APPELER EN CAS DE NOUVELLE CONNEXIONS			  //
	try
	{
		Client tempUser(fd, nick, name, *this);
		_clientList.push_back(tempUser);
		tempUser.comfirmConnexion();
	}
	catch (Client::AlreadyUsedParametersException &exception)
	{
		std::cout << exception.what() << std::endl;
		//Ce message d'exception doit peut-être être renvoyé au client également
	}

//					LIGNES A APPELER EN CAS DE RECEPTION DE COMMANDES		  //
	try
	{
		Client tempUser = getClientFromInfo(fd); // FD est détécté par poll
		std::string command = "/JOIN LePlusBeauChannel"; //command est read depuis le fd
		tempUser.command(command);
	}
	catch (Client::ErrorInCommandException exception)
	{
		std::cout << exception.what() << std::endl;
		//Ce message d'exception doit peut-être être renvoyé au client également
	}
	catch (Server::ClientNotFoundException exception)
	{
		std::cout << exception.what() << std::endl;
	}
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

int	Server::getPort(void) const
{
	return _port;
}

std::string Server::getPassword(void) const
{
	return _password;
}

std::vector<Client>	Server::getClientList(void) const
{
	return (_clientList);
}

Client Server::getClientFromInfo(int fd) const
{
	for (std::vector<Client>::const_iterator it = _clientList.begin(); it != _clientList.end(); it++)
		if (fd == (*it).getFd())
			return (*it);
	throw Server::ClientNotFoundException();
}

Client Server::getClientFromInfo(std::string nickname) const
{
	for (std::vector<Client>::const_iterator it = _clientList.begin(); it != _clientList.end(); it++)
		if (nickname.compare((*it).getNickname()) != 0)
			return (*it);
	throw Server::ClientNotFoundException();
}

/* ************************************************************************** */