/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magostin <magostin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 00:15:21 by magostin          #+#    #+#             */
/*   Updated: 2022/03/24 02:03:22 by magostin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int	ft_error(std::string str)
{
	std::cout << str << std::endl;
	return (1);
}

bool str_is_digits(const std::string &str)
{
	return str.find_first_not_of("0123456789") == std::string::npos;
}

int main(int ac, char **av)
{
	Server	myServer;
	if (ac != 3)
		return (ft_error("Usage : ./ft_irc <port> <password>"));
	if (!str_is_digits(std::string(av[1])))
		return (ft_error("Port must be digits"));

	myServer = Server(atol(av[1]), av[2]);
	myServer.start();
}