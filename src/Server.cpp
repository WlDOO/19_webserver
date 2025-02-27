/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:32:31 by najeuneh          #+#    #+#             */
/*   Updated: 2025/02/24 11:13:26 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

Server::Server() {}

Server::~Server() {}

void	Server::accept_new_connection(int server_socket, std::vector<struct pollfd> &poll_fds, int *poll_count, int *poll_size)
{
	Server serv;
	int 	client_fd;
	char	msg_to_send[BUFSIZ];
	int		status;
    std::ostringstream oss;

	client_fd = accept(server_socket, NULL, NULL);
	if (client_fd == -1)
	{
		std::cerr << "[server] Accept error " << strerror(errno) << std::endl;
		return ;
	}
	serv.add_to_poll_fds(poll_fds, client_fd, poll_count, poll_size);
	std::cout << "[server] Accepted new connection on client socket" << client_fd << std::endl;
	oss << "Welcome. You are client fd: " << client_fd << std::endl;
	std::string msg = oss.str();
	std::strncpy(msg_to_send, msg.c_str(), BUFSIZ - 1);
	msg_to_send[BUFSIZ - 1] = '\0';	
	status = send(client_fd, msg_to_send, std::strlen(msg_to_send), 0);
	if (status == -1)
		std::cerr << "[Server] Send error to client " << client_fd << ": " << strerror(errno) << std::endl;
}

void Server::add_to_poll_fds(std::vector<struct pollfd> &poll_fds, int new_fd, int *poll_count, int *poll_size)
{
	if (*poll_count == *poll_size)
	{
		*poll_size *= 2;
		poll_fds.resize(*poll_size);
	}
	poll_fds[*poll_count].fd = new_fd;
	poll_fds[*poll_count].events = POLLIN;
	(*poll_count)++;
}

void	Server::del_from_poll_fds(std::vector<struct pollfd> &poll_fds, int i, int *poll_count)
{
	poll_fds[i] = poll_fds[*poll_count - 1];
	(*poll_count)--;
}
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

	std::cout << "[server] Listening on port: " << 4242 << std::endl;
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
			_exit(1);
		}
		else if (status == 0)
		{
			std::cout << "[server] Waiting... " << poll_count << std::endl;
			
			continue;
		}
		for (int i = 0; i < poll_count; i++)
		{
			if ((poll_fds[i].revents & POLLIN) != 1)
				continue ;
			std::cout << poll_fds[i].fd << " ready for I/O operation" << std::endl;
			if (poll_fds[i].fd == server_socket)
				accept_new_connection(server_socket, poll_fds, &poll_count, &poll_size);
			else
				read_data_from_socket(i, poll_fds, &poll_count, server_socket);
		}
	}
	return (0);
}

void Server::read_data_from_socket(int i, std::vector<struct pollfd> &poll_fds, int *poll_count, int server_socket) {

	char buffer[BUFSIZ];
    char msg_to_send[BUFSIZ];
    int bytes_read;
    int status;
    int dest_fd;
    int sender_fd;

	sender_fd = (poll_fds)[i].fd;
	memset(&buffer, '\0', sizeof buffer);
	bytes_read = recv(sender_fd, buffer, BUFSIZ, 0);
	if (bytes_read <= 0) {
		if (bytes_read == 0) {
			std::cout << sender_fd << " Client socket closed connection." << std::endl;
		}
		else {
			std::cerr << "[Server] Recv error: " << strerror(errno);
		}
		close(sender_fd); // Ferme la socket
		del_from_poll_fds(poll_fds, i, poll_count);
    }
    else {
        std::cout << sender_fd << "Got message: " << buffer << std::endl;

        memset(&msg_to_send, '\0', sizeof msg_to_send);
        sprintf(msg_to_send, "[%d] says: %s", sender_fd, buffer);
        for (int j = 0; j < *poll_count; j++) {
            dest_fd = (poll_fds)[j].fd;
            if (dest_fd != server_socket && dest_fd != sender_fd) {
                status = send(dest_fd, msg_to_send, strlen(msg_to_send), 0);
                if (status == -1) {
                    std::cerr << "[Server] Send error to client fd" << dest_fd << strerror(errno);
                }
            }
        }
    }
}


int Server::create_server(void)
{
	struct sockaddr_in	sa;
	int					socket_fd;
	int					status;
	
	memset(&sa, 0, sizeof sa);
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	sa.sin_port = htons(4242);

	socket_fd = socket(sa.sin_family, SOCK_STREAM, 0);
    if (socket_fd == -1) {
        std::cerr << "[Server] Socket error: " << strerror(errno) << std::endl;
        return -1;
    }
	std::cout << "Server created socket fd:" << socket_fd << std::endl;
	status = bind(socket_fd, (struct sockaddr *)&sa, sizeof sa);
	if (status != 0)
	{
		std::cerr << "bind " << strerror(errno);
		return -1;
	}
	std::cout << "New connectiom1 socket fd:" << socket_fd << std::endl;
	return socket_fd;
}

int main(int ac, char **av)
{
	Server serv;
	
	int status;
	(void)av;
	(void)ac;
	status = serv.sondage_poll();
}