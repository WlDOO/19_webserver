/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najeuneh <najeuneh@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:42:58 by najeuneh          #+#    #+#             */
/*   Updated: 2025/03/13 16:37:51 by najeuneh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <sys/stat.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <fcntl.h>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <cerrno>
#include <map>

struct Location
{
	std::string	Location;
	std::string	root;
	std::string	index;
	std::string	autoindex;
	std::string	redirect_url;
	std::string	upload_store;
	std::string	directory_listening;
	std::vector<std::string>	cgi_pass;
	std::vector<std::string>	methods;
	std::vector<std::string>	cgi_extonsions;
};

struct Server
{
	std::string	root;
	std::string host;
	std::string	server_name;
	std::string	client_max_body_size;
	std::vector<std::string>	error_page_num;
	std::vector<std::string>	error_page_loc;
	std::vector<std::string>	listen;
	std::vector<Location>		Loc;
	int size;
};



class Config
{
	private:
		int	size_serv;
	public:
		std::vector<Server> Server;
		Config	Config_file(std::string str2);
		int		CheckServer(std::string str);
		void	SetServer(std::string str);
		void	SetLoc(std::string str);
		Config();
		~Config();
};

std::string	pick_file(std::string str);
void removeExtraWhitespace(std::string& str);
bool isWhitespace(char c);
bool	isIp(std::string ip);
bool isDirectory(const std::string& path);
int	CheckServer_name(std::string str);
