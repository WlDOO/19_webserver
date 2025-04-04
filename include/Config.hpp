/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:42:58 by najeuneh          #+#    #+#             */
/*   Updated: 2025/04/04 02:28:39 by rafnasci         ###   ########.fr       */
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
	std::string	alias;
	std::string	directory_listening; //
	std::vector<std::string>	cgi_pass;
	std::vector<std::string>	methods;
	std::vector<std::string>	cgi_extonsions;
	std::string					script;
};

struct Server_pars
{
	std::string index;
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
		std::vector<Server_pars> Server_par;
		Config	Config_file(std::string str2);
		int		CheckServer(std::string str);
		void	SetServer(std::string str);
		void	SetLoc(std::string str);
		Config();
		~Config();
};

int	parse_file(Config Conf);
std::string	pick_file(std::string str);
void removeExtraWhitespace(std::string& str);
bool isWhitespace(char c);
bool	isIp(std::string ip);
bool isDirectory(const std::string& path);
int	CheckServer_name(std::string str);
Config	setpath(Config Conf);
