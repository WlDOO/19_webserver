/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:32:31 by najeuneh          #+#    #+#             */
/*   Updated: 2025/03/12 15:51:24 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

Server::Server(const std::vector<int>& ports)
{
	for (size_t i = 0; i < ports.size(); i++)
   		setupSocket(ports[i]);
    setupEpoll();
}

Server::~Server()
{
	for (size_t i = 0; i < server_fds.size(); i++)
   		close(server_fds[i]);
    close(epoll_fd);
}

void Server::handleConnections() {
    struct epoll_event events[MAX_EVENTS];
    while (true) {
        int event_count = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);  //return the number of triggered (new conenctions or data) events
		if (event_count == -1)
		{
			perror("Epoll wait failled");
			exit(EXIT_FAILURE);
		}
		for (int i = 0; i < event_count; i++) {
			int event_fd = events[i].data.fd;
            if (std::find(server_fds.begin(), server_fds.end(), event_fd) != server_fds.end()) {
                // New connection
                struct sockaddr_in client_addr; 
                socklen_t client_len = sizeof(client_addr);
                int client_fd = accept(event_fd, (struct sockaddr*)&client_addr, &client_len);  // retrieves the new client ocnneciton and open a new socket to communicate
                if (client_fd < 0)
				{
                    perror("Accept failed");
                    continue;
                }

                fcntl(client_fd, F_SETFL, O_NONBLOCK);  // makes the client socket non blocking
                struct epoll_event client_event;
                client_event.events = EPOLLIN | EPOLLOUT;  // epoll watches for both reading and writing event
                client_event.data.fd = client_fd;  // socket of the client

                epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &client_event);  // registers the client to the epoll instance
                std::cout << "New client connected: " << client_fd << std::endl;
            } else if (events[i].events && EPOLLIN) {  //ici on gere les pollin
                // Handle client request
				read_data_from_socket(i, events);
            } 
			// else if (events[i].events & EPOLLOUT) {  ////ici on gere les POLLOUT
			// 	// send_data_to_socket(i, events);
			// }
        }
    }
}

void Server::setupEpoll() {
    epoll_fd = epoll_create1(0);  // creates epoll instance
    if (epoll_fd == -1) {
        perror("Epoll creation failed");
        exit(EXIT_FAILURE);
    }

	for (size_t i = 0; i < server_fds.size(); i++)
	{
		struct epoll_event event;  // structure to store information about what we want to monitor
		event.events = EPOLLIN; // watch for incoming data/new connections
		event.data.fd = server_fds[i];  

		if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_fds[i], &event) == -1)  // adds server_fd to the epoll watch list
		{
			perror("Epoll add failed");
			exit(EXIT_FAILURE);
		}
	}
}

void Server::setupSocket(int port)
{
	int server_fd;
	sockaddr_in	address;
	address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
	
    server_fd = socket(address.sin_family, SOCK_STREAM, 0);
    if (server_fd == -1)
	{
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)); //allows reusin the same address if the server restarts quickly
	// int keepalive = 1;
    // setsockopt(server_fd, SOL_SOCKET, SO_KEEPALIVE, &keepalive, sizeof(keepalive));
	
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0)
	{
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, SOMAXCONN) < 0)  //socket is ready to accept connections
	{
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    fcntl(server_fd, F_SETFL, O_NONBLOCK); // Make it non-blocking
	server_fds.push_back(server_fd);  //store the socket for epoll
	std::cout << "Server created socket fd:" << server_fd << std::endl;
    std::cout << "Server started on port " << port << std::endl;
}

void Server::run() {
    handleConnections();
}

int main(int ac, char **av)
{
	(void)av;
	(void)ac;


	std::vector<int> ports;  // les ports qu'on veut utiliser
	ports.push_back(4242);
	ports.push_back(8001);
	
	Server serv(ports);
	serv.run();
	return (0);
}