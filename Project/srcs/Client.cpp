#include "Client.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Client::Client( const Client & src ) : _server(src._server)
{
	*this = src;
}

Client::Client(struct pollfd fd, std::string nickname, std::string username, Server &server)
: _nickname(nickname), _username(username), _fd(fd), _server(server)
{
	std::vector<Client> clientList = _server.getClientList();
	for (std::vector<Client>::iterator it = clientList.begin(); it != clientList.end(); it++)
	{
		if (_nickname.compare((*it)._nickname) != 0)
			throw Client::AlreadyUsedParametersException("❌ Nickname is already used ❌");
		if (_fd.fd == (*it)._fd.fd)
			throw Client::AlreadyUsedParametersException("❌ File Descriptor is already used ❌");
	}
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Client::~Client()
{
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Client &				Client::operator=( Client const & rhs )
{
	_nickname = rhs._nickname;
	_username = rhs._username;
	_fd = rhs._fd;
	return *this;
}

std::ostream &			operator<<( std::ostream & o, Client const & i )
{
	o << "I am " << i.getNickname() << " with fd " << i.getFd();
	return o;
}


/*
** --------------------------------- METHODS ----------------------------------
*/

void	Client::confirmConnexion(void)
{
	write(_fd.fd, "Some Confirmation Message", 26);
}

void	Client::command(std::string command)
{
	std::vector<std::string> args;
	std::size_t found = command.find_first_of(" ");
	std::size_t first = 0;
	while (found != std::string::npos)
	{
		args.push_back(command.substr(first, found - first));
		first = found;
		found = command.find_first_of(" ",found + 1);
	}
	for (std::vector<std::string>::iterator it = args.begin() ; it != args.end() ; it++)
	{
		std::cout << *it << std::endl;
	}
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

int			Client::getFd(void) const
{
	return (_fd.fd);
}

std::string	Client::getNickname(void) const
{
	return (_nickname);
}

std::string	Client::getUsername(void) const
{
	return (_username);
}

/* ************************************************************************** */