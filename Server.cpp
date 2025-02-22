/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najeuneh <najeuneh@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:32:31 by najeuneh          #+#    #+#             */
/*   Updated: 2025/02/21 18:18:32 by najeuneh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <stdio.h>
#include <string.h>
#include <vector>

Server::Server() {}

Server::~Server() {}

int	Server::sondage_poll(void)
{
	Server serv;

	int server_socket;
	int status;

	std::vector<struct pollfd> poll_fds;
	int				poll_size;
	int				poll_count;

	std::cout << "---- SERVER ----" << std::endl << std::endl;
	server_socket = serv.create_server();
	if (server_socket == -1)
	{
		return 1;
	} 

	std::cout << "[server] Listening on port" << 4242 << std::endl;
	status = listen(server_socket, 10);
	if (status != 0)
	{
		std::cerr << "[server] Listen error: " << strerror(errno) << std::endl;
		return 3;
	}

    // Préparation du tableau des descripteurs de fichier pour poll()
    // On va commencer avec assez de place pour 5 fds dans le tableau,
    // on réallouera si nécessaire

	poll_size =  5;
	poll_fds.resize(poll_size);

    // Ajoute la socket du serveur au tableau
    // avec alerte si la socket peut être lue
	poll_fds[0].fd = server_socket;
	poll_fds[0].events = POLLIN;
	poll_count = 1;
	
	std::cout << "[server] set up poll fd array " << strerror(errno) << std::endl;
	while(1)
	{
		status = poll(poll_fds.data() , poll_count, 2000);
		if (status == -1)
		{
			std::cerr << "[server] poll error: " << strerror(errno) << std::endl;
			exit(1);
		}
		else if (status == 0)
		{
			std::cout << "[server] Waiting..." << std::endl;
			continue;
		}
		for (int i = 0; i < poll_count; i++)
		{
			if ((poll_fds[i].revents & POLLIN) != 1)
				continue ;
			std::cout << poll_fds[i].fd << "ready for I/O operation" << std::endl;
			if (poll_fds[i].fd == server_socket)
				accept_new_connection(server_socket, &poll_fds, &poll_count, &poll_size);
		}
		
	
	}
}

int Server::create_server(void)
{
	struct sockaddr_in	sa;
	int					socket_fd;
	int					client_fd;
	int					status;

	struct sockaddr_storage client_addr;
	socklen_t	addr_size;
	memset(&sa, 0, sizeof sa);
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	sa.sin_port = htons(4242);

	socket_fd = socket(sa.sin_family, SOCK_STREAM, 0);
	status = bind(socket_fd, (struct sockaddr *)&sa, sizeof sa);
	if (status != 0)
	{
		std::cerr << "bind " << strerror(errno);
		return 2;
	}
	listen(socket_fd, 10);

	addr_size = sizeof client_addr;
	client_fd = accept(socket_fd, (struct sockaddr *)&client_addr, &addr_size);
	if (client_fd == -1)
	{
		std::cerr << "accept " << strerror(errno);
		return 3;
	}
	std::cout << "New connectiom1 socket fd:" << socket_fd << "client fd: " << client_fd << std::endl;
	return 0;
}

int main(int ac, char **av)
{
	Server serv;
	
	int status;

	status = serv.create_server();
}