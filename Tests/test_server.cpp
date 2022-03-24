#include <ostream>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SOCKET int
#define INVALID_SOCKET -1

int main()
{
	SOCKET server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (server == INVALID_SOCKET)
	{
		std::cout << "Erreur initialisation socket";
		return -2;
	}

	const unsigned short port = 9999;
	sockaddr_in addr;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;

	int res = bind(server, (sockaddr*)&addr, sizeof(addr));
	if (res != 0)
	{
		std::cout << "Erreur bind";
		return -3;
	}

	res = listen(server, SOMAXCONN);
	if (res != 0)
	{
		std::cout << "Erreur listen";
		return -4;
	}

	std::cout << "Serveur demarre sur le port " << port << std::endl;

	sockaddr_in from = { 0 };
	socklen_t addrlen = sizeof(addr);
	SOCKET newClient = accept(server, (sockaddr*)(&from), &addrlen);
	if (newClient != INVALID_SOCKET)
	{
		char buff[INET6_ADDRSTRLEN] = { 0 };
		std::string clientAddress = inet_ntop(addr.sin_family, (void*)&(addr.sin_addr), buff, INET6_ADDRSTRLEN);
		std::cout << "Connexion de " << clientAddress.c_str() << ":" << addr.sin_port << std::endl;
	}
	close(server);
	return 0;
}