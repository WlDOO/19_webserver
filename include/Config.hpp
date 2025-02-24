/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najeuneh <najeuneh@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:42:58 by najeuneh          #+#    #+#             */
/*   Updated: 2025/02/24 18:16:35 by najeuneh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <unistd.h>  // Pour read(), close()
#include <fcntl.h>   // Pour open()
#include <vector>
#include <map>

typedef	struct Location
{
	std::string Location;
	std::string	root;
	std::string	index;
	std::string redirect_url;
	std::string	upload_store;
	std::string	cgi_pass;
	bool directory_listening;
	std::vector<std::string> methods;
	std::vector<std::string>cgi_extonsions;
};

typedef struct Server
{
	std::string host;
	std::string	server_name;
	std::string	client_max_body_size;
	std::vector<std::string> listen;
	std::map<std::string, std::string>	error_page;
};



class Config
{
	private:
		Server Server;
		std::vector<Location> Loc;
	public:
		Config	Config_file(int fd);
		std::string	GetLoc(int i, int y);
		int	CheckServer(int i, std::string	str);
		int	CheckLoc(int i, std::string	str);
		int NextLigne(int i, std::string str);
		Config();
		~Config();
};



