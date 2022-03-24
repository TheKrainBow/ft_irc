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

//pour start
int sock_bind_listen(const sockaddr_in *addr, int fd)
{
    if (bind(fd, (const sockaddr *)addr, sizeof(*addr)))
        return (-1);
    if (listen(fd, SOMAXCONN))//SOMAXCONN laisse le systeme choisir le nombre max de connections
        return (-2);
    return (0);
}

//pour start
int sock_bind_listen(const sockaddr_in *addr)
{
    int fd = socket(PF_INET6, SOCK_STREAM, 0); //PF_INET6 pour IPv6, SOCK_STREAM est securise et ne fixe pas une taille de paquet
    if (bind(fd, (const sockaddr *)addr, sizeof(*addr)))
        return (-1);
    if (listen(fd, SOMAXCONN))//SOMAXCONN laisse le systeme choisir le nombre max de connections
        return (-2);
    return (fd);
}

//pour start
int initSock(sockaddr_in *addr, long port, int fd)
{
    addr->sin_addr.s_addr = INADDR_ANY; //pour choper toutes les connections, locales ou non
    addr->sin_port = htonl(port);
    addr->sin_family = AF_INET6; //pour choper les IPv6
    //addr->sin_zero sert a rien, juste a s'assurer que la structure prenne 16 octets
    if (sock_bind_listen(addr, fd))
        return (-1);
    return (0);
}

int		Server::start(void)
{
//						LIGNES POUR SUPPRIMER LES ERREURS:					  //

//							 GESTION DES CONNEXIONS ICI					 	  //

	char	buffer[BUFFER_SIZE];

//mise em place de la socket qui ecoute au port donne en argument du programme
	struct pollfd listening;
	listening.fd = socket(PF_INET6, SOCK_STREAM, 0); //PF_INET6 pour IPv6, SOCK_STREAM est securise et ne fixe pas une taille de paquet
    fcntl(listening.fd, F_SETFL, O_NONBLOCK); //pour que la socket soit non-blocante
	listening.events = POLLIN; //event "il y a des donnees en attente de lecture"
	sockaddr_in addr;
    if (initSock(&addr, _port, listening.fd))
        return (ERR_SOCKET);
//																			  //
    socklen_t size = sizeof(addr);
	std::vector<struct pollfd> toMonitor; //tableau des fd a surveiller ave poll()
	toMonitor.push_back(listening);

//
    sockaddr_in addrNewClient;
	struct pollfd	newClient;
	while (poll(&toMonitor[0], toMonitor.size(), -1) > 0)
	{
		newClient.fd = accept(listening.fd, (sockaddr *)&addr, &size); //va bloquer jusqu'a avoir au moins une tentative de connexion
		if (newClient.fd > 0)
		{
    		fcntl(newClient.fd, F_SETFL, O_NONBLOCK); //pour que la socket soit non-blocante
			sock_bind_listen(&addrNewClient, newClient.fd);
			toMonitor.push_back(newClient);
			//TODO : creer un nouveau Client ?
		}
		for () //ici, iterer sur toMonitor pour le recv
	}
	
//																			  //

//					LIGNES A APPELER EN CAS DE NOUVELLE CONNEXIONS			  //
	try
	{
		Client tempUser(fd, nick, name, *this);
		_clientList.push_back(tempUser);
		tempUser.confirmConnexion();
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