#include "Server.hpp"


/*TODO : fonctions a coder */


/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Server::Server() {
	_port = -1;
	_password = "";
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

void	Server::createClient(pollfd fd, char *buffer)
{
//Mathieu, cette fonction est toute a toi :3
	(void)fd;
	(void)buffer;
}

void	Server::removeClient(pollfd *tab, int i, int &size)
{
	_clientList.erase(_clientList.find(tab[i].fd));
	tab[i] = tab[size - 1];
	size--;
}

//pour start
int sock_bind_listen(const sockaddr_in *addr, int fd)
{
	if (bind(fd, (const sockaddr *)addr, sizeof(sockaddr)))
		return (-1);
	if (listen(fd, SOMAXCONN))//SOMAXCONN laisse le systeme choisir le nombre max de connections
		return (-2);
	return (0);
}

//pour start
int sock_bind_listen(const sockaddr_in *addr)
{
	int fd = socket(PF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0); //PF_INET6 pour IPv6, SOCK_STREAM est securise et ne fixe pas une taille de paquet
	if (bind(fd, (const struct sockaddr *)addr, sizeof(*addr)))
		return (-1);
	if (listen(fd, SOMAXCONN))//SOMAXCONN laisse le systeme choisir le nombre max de connections
		return (-2);
	return (fd);
}

//pour start
int initSock(sockaddr_in *addr, int port, int fd)
{
	addr->sin_addr.s_addr = INADDR_ANY; //pour choper toutes les connections, locales ou non
	addr->sin_port = htons(port);
	addr->sin_family = AF_INET; //pour choper les IPv4
	//addr->sin_zero sert a rien, juste a s'assurer que la structure prenne 16 octets
	if (sock_bind_listen(addr, fd) < 0)
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
	listening.fd = socket(PF_INET, SOCK_STREAM/* | SOCK_NONBLOCK*/, 0); //PF_INET pour IPv4, SOCK_STREAM est securise et ne fixe pas une taille de paquet
	listening.events = POLLRDNORM; //event "il y a des donnees en attente de lecture"
	sockaddr_in addr;
	if (initSock(&addr, _port, listening.fd))
		return (ERR_SOCKET);
	
	socklen_t size = sizeof(addr);
	pollfd toMonitor[256]; //tableau des fd a surveiller ave poll()
	int		sizeToMonitor = 1;
	toMonitor[0] = listening;

	sockaddr_in addrNewClient;
	struct pollfd	newClient;
	while (poll(toMonitor, sizeToMonitor, -1) > 0)

	{
		std::cout << "boucle " ;
		newClient.fd = accept(listening.fd, (sockaddr *)&addr, &size);
		if (newClient.fd > 0 && sizeToMonitor < 256)
		{
			sock_bind_listen(&addrNewClient, newClient.fd);
			if (recv(newClient.fd, buffer, sizeof(char) * BUFFER_SIZE, 0) > 0)
			{
				try
				{
					createClient(newClient, buffer);
					(_clientList.find(newClient.fd))->second.confirmConnexion();
					toMonitor[sizeToMonitor] = newClient;
					sizeToMonitor++;
				}
				catch (std::exception& e){}
			}
		}
		for (int i = 1; i < sizeToMonitor; i++)
		{
			if (toMonitor[i].revents == POLLHUP) //le client s'est deconnecte
				removeClient(toMonitor, i, sizeToMonitor);
			if (recv(toMonitor[i].fd, buffer, sizeof(char) * BUFFER_SIZE, MSG_DONTWAIT) > 0)
				(_clientList.find(toMonitor[i].fd))->second.command(static_cast<std::string>(buffer));
		}
	}
	std::cout << "Sorti du while infini" << std::endl;
	
//																			  //
/*
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
	*/
	return (0);
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

std::map<int, Client>	Server::getClientList(void) const
{
	return (_clientList);
}

Client Server::getClientFromInfo(int fd) const
{
	for (std::map<int, Client>::const_iterator it = _clientList.begin(); it != _clientList.end(); it++)
		if (fd == it->second.getFd())
			return (it->second);
	throw Server::ClientNotFoundException();
}

Client Server::getClientFromInfo(std::string nickname) const
{
	for (std::map<int, Client>::const_iterator it = _clientList.begin(); it != _clientList.end(); it++)
		if (nickname.compare((it->second).getNickname()) != 0)
			return (it->second);
	throw Server::ClientNotFoundException();
}

/* ************************************************************************** */