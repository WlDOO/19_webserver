/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raf <raf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:32:12 by najeuneh          #+#    #+#             */
/*   Updated: 2025/06/17 16:19:51 by raf              ###   ########.fr       */
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
#include <sys/wait.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include "Config.hpp"
#include "Cgi.hpp"
#pragma once

#define MAX_EVENTS 30 // nombre de client max
#define BUFFER_SIZE 1024
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define BLUE    "\033[34m"
#define GREEN   "\033[32m"

uint32_t htonl(uint32_t hostlong);  //"Host to network long"
uint16_t htons(uint16_t hostshort); //"Host to network short"
uint32_t ntohl(uint32_t netlong);   //"Network to host long"
uint16_t ntohs(uint16_t netshort);  //"Network to host short"
//inet_pton << "pton” veut dire " presentation to network" ou, en français “présentation au réseau”

class Cgi;

class Server
{
	private:
		
		Cgi*		cgi;
		Config		Conf;

		std::string _Script;
		std::string _Script_path;
		std::string _Request_type;
		std::string _Request_content;
		std::string _Request_html;
		std::string _Post_content;
		std::string _Post_file_name;
		std::string _Autoindex_output;
		std::string _Cgi_output;
		bool		_Keep_alive;

		int			_Error_post;
		int			_Http_code;
		int			_Is_autoindex;
		int			_Is_cgi;

		int			_server_index;

		void				handleKeepAlive(const std::string &request);

		//Server
		std::vector<int>	server_fds;
		int					epoll_fd;
		void				setupSocket(int port);
		void				setupEpoll();
		void				handleConnections();

	public:
	
		void	SetConf(Config config);
		Server(const std::vector<int>& ports, Config conf);
		
		//Autoindex
		int			generate_autoindex(std::string loc, int index_loc);

		//HtmlAuto
		std::string html_success(int code, const std::string& web_page);
		std::string html_error(int code);
		std::string	html_error_gen(int error_code, const std::string& msg);
		std::string	get_msg(int code);
		std::string	check_error_dir(int code);
		//Flavico

		//Server
		void run();
		//Logs
		void		print_logs(std::string user, std::string message, int code);
		//Parse_request
		int			parse_request(void);
		int			check_vectors(std::vector<std::string> vector, std::string to_find);
		int			check_cgi(int index_loc);
		int			check_autoindex(int index_loc, std::string loc);
		int			allowed_method(int index_loc);
		std::string	handle_alias(std::string alias, std::string loc);
		//Read_send
		void 		read_data_from_socket(int i, struct epoll_event events[MAX_EVENTS]);
		void		send_data_to_socket(int i, struct epoll_event events[MAX_EVENTS]);
		std::string read_html_file(const std::string& file_path);
		std::string html_response(int client_fd, std::string web_page);
		int			set_request_type(char buffer[BUFSIZ]);
		std::string	html_request(int client_fd);
		int			set_request_http(std::string sender_msg);
		std::string	request_get(int client_fd, int code);
		int			request_post(void);
		std::string request_delete(int client_fd);
		int			content_del(std::string full_msg);
		int			set_content_post(std::string full_msg);
		int			content_post_file(std::string full_msg);
		std::string	set_params_file(std::string full_msg, std::string to_find, std::string to_find2);
		int			content_post_cgi(std::string full_msg);
		std::string html_outputs(int client_fd);
		int			redirect(int index_loc);
		
		~Server();
};