/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najeuneh <najeuneh@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:42:58 by najeuneh          #+#    #+#             */
/*   Updated: 2025/02/25 19:18:50 by najeuneh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <unistd.h>  // Pour read(), close()
#include <fstream>
#include <sstream>
#include <fcntl.h>   // Pour open()
#include <string>
#include <vector>
#include <map>

struct Location
{
	std::string Location;
	std::string	root;
	std::string	index;
	std::string redirect_url;
	std::string	upload_store;
	std::string	cgi_pass;
	std::string directory_listening;
	std::vector<std::string> methods;
	std::vector<std::string>cgi_extonsions;
};

struct Server
{
	std::string host;
	std::string	server_name;
	std::string	client_max_body_size;
	std::vector<std::string> listen;
	std::string	error_page_num;
	std::string	error_page_loc;
	std::vector<Location> Loc;
	int size;
};



class Config
{
	private:
	public:
		Server Server;
		Config	Config_file(std::string str2);
		int	CheckServer(int i, std::string str);
		void	SetServer(std::string str);
		void	SetLoc(std::string str);
		Config();
		~Config();
};



