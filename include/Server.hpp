/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:32:12 by najeuneh          #+#    #+#             */
/*   Updated: 2025/02/25 12:42:32 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>	//getaddrinfo
#include <sys/socket.h>
#include <sys/poll.h>
#include <iostream>
#include <sstream>
#include <cstring>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <unistd.h>
#include <cerrno>
#pragma once

#define PORT 4242;

uint32_t htonl(uint32_t hostlong);  //"Host to network long"
uint16_t htons(uint16_t hostshort); //"Host to network short"
uint32_t ntohl(uint32_t netlong);   //"Network to host long"
uint16_t ntohs(uint16_t netshort);  //"Network to host short"
//inet_pton << "pton” veut dire " presentation to network" ou, en français “présentation au réseau”

class Server
{
	private:
		
	public:
		Server();
		void accept_new_connection(int server_socket, std::vector<struct pollfd> &oll_fds, int *poll_count, int *poll_size);
		void add_to_poll_fds(std::vector<struct pollfd> &poll_fds, int new_fd, int *poll_count, int *poll_size);
		void del_from_poll_fds(std::vector<struct pollfd> &poll_fds, int i, int *poll_count);
		void read_data_from_socket(int i, std::vector<struct pollfd> &poll_fds, int *poll_count, int server_socket);
		int	sondage_poll(void);
		int	create_server(void);
		~Server();
};
