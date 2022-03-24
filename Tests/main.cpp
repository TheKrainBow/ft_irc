#include "includes.hpp"

int test_args(int ac, char **av)
{
    int i = 0;
    if (ac != 3)
    {
        std::cout << "Usage : ./ft_irc <port> <password>" << std::endl;
        return (1);
    }
    while(av[1][i])
    {
        if (!isdigit(av[1][i]))
        {
            std::cout << "Usage : the port must be numerical" << std::endl;
            return (2);
        }
    }
    return (0);
}
int sock_bind_listen(const sockaddr_in *addr, int fd)
{
    if (bind(fd, (const sockaddr *)addr, sizeof(*addr)))
        return (-1);
    if (listen(fd, SOMAXCONN))//SOMAXCONN laisse le systeme choisir le nombre max de connections
        return (-2);
    return (0);
}

int sock_bind_listen(const sockaddr_in *addr)
{
    int fd = socket(PF_INET6, SOCK_STREAM, 0); //PF_INET6 pour IPv6, SOCK_STREAM est securise et ne fixe pas une taille de paquet
    if (bind(fd, (const sockaddr *)addr, sizeof(*addr)))
        return (-1);
    if (listen(fd, SOMAXCONN))//SOMAXCONN laisse le systeme choisir le nombre max de connections
        return (-2);
    return (fd);
}

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

int main(int ac, char **av)
{
    if (test_args(ac, av))
        return (ERR_ARG);
    int fd = socket(PF_INET6, SOCK_STREAM, 0); //PF_INET6 pour IPv6, SOCK_STREAM est securise et ne fixe pas une taille de paquet
    sockaddr_in *addr = new sockaddr_in;
    if (initSock(addr, atol(av[1]), fd))
        return (ERR_SOCKET);
    socklen_t size = sizeof(*addr);
    int portNewClient = accept(fd, (sockaddr *)addr, &size); //va bloquer jusqu'a avoir au moins une tentative de connexion
    sockaddr_in *addrNewClient = new sockaddr_in; //TODO : il faudrait faire une liste chainee des clients a surveiller avec poll
    sock_bind_listen(addrNewClient, portNewClient);
    while (poll() > 0)
    {
        //trucs


        portNewClient = accept();
    }
}