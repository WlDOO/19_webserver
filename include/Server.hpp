/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:32:12 by najeuneh          #+#    #+#             */
/*   Updated: 2025/03/08 16:33:09 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cerrno>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#pragma once


#define MAX_EVENTS 30 // nombre de client max
#define BUFFER_SIZE 1024

uint32_t htonl(uint32_t hostlong);  //"Host to network long"
uint16_t htons(uint16_t hostshort); //"Host to network short"
uint32_t ntohl(uint32_t netlong);   //"Network to host long"
uint16_t ntohs(uint16_t netshort);  //"Network to host short"
//inet_pton << "pton” veut dire " presentation to network" ou, en français “présentation au réseau”

class Server
{
	private:
		
		std::string _Request_type;
		std::string _Request_content;
		std::string _Request_html;
		std::string _Post_content;
		std::string _Post_file_name;
		int			_Keep_alive;

		//Server
		std::vector<int>	server_fds;
		int					epoll_fd;
		void				setupSocket(int port);
		void				setupEpoll();
		void				handleConnections();

	public:
	
		Server(const std::vector<int>& ports);
		
		//Server
		void run();
		
		//Read_send
		void 		read_data_from_socket(int i, struct epoll_event events[MAX_EVENTS]);
		void		send_data_to_socket(int i, struct epoll_event events[MAX_EVENTS]);
		std::string read_html_file(const std::string& file_path);
		std::string html_error_404(int client_fd);
		std::string html_response(int client_fd, std::string web_page);
		void		set_request_type(char buffer[BUFSIZ]);
		std::string	html_request(int client_fd);
		std::string	request_get(int client_fd);
		std::string	request_post(int client_fd, std::string file_name);
		void		set_content_post(std::string full_msg);
		
		~Server();
};