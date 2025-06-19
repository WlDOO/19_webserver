/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raf <raf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:32:31 by najeuneh          #+#    #+#             */
/*   Updated: 2025/06/19 13:29:29 by raf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"
#include "../include/Config.hpp"
#include "../include/Cgi.hpp"

Server::Server(const std::vector<int>& ports, Config conf) : cgi(new Cgi())
{
	for (size_t i = 0; i < ports.size(); i++)
   		setupSocket(ports[i]);
    setupEpoll();
	SetConf(conf);
}

Server::~Server()
{
	for (size_t i = 0; i < server_fds.size(); i++)
   		close(server_fds[i]);
    close(epoll_fd);
	delete cgi;
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
            } else if (events[i].events && EPOLLIN) {
				read_data_from_socket(i, events);
            } 
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
}

void Server::run() {
    handleConnections();
}

void	Server::SetConf(Config config)
{
	this->Conf = config;
}


int main(int ac, char **av)
{
	std::string str;
	if (ac == 1)
	{
		str = "Configuration/Good.conf";
	}
	else if (ac == 2)
	{
		str = av[1];
	}
	else
	{
		std::cerr << "Args error" << std::endl;
		return (1);	
	}
	Config Conf;
	if (str.find(".conf") == std::string::npos)
	{
		std::cerr << "Config file must have .conf extension" << std::endl;
		return (2);
	}
	std::string str2;
	
	str2 = pick_file(str);
	Conf = Conf.Config_file(str2);
	if (parse_file(Conf) == 0)
		return 0;
	std::vector<int> ports;  // les ports qu'on veut utiliser
	for (long unsigned int i = 0; i < Conf.Server_par.size(); i++)
	{
		for (size_t x = i + 1; x < Conf.Server_par.size(); x++)
		{
			if (x < Conf.Server_par.size() && Conf.Server_par[i].listen[0] == Conf.Server_par[x].listen[0])
			{
				std::cerr << "Using same Port for different severs." << std::endl;
				return (3);
			}
		}	
		ports.push_back(atoi(Conf.Server_par[i].listen[0].c_str()));
	}
	Server serv(ports, Conf);
	serv.run();
	return (0);
}