/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najeuneh <najeuneh@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:46:38 by najeuneh          #+#    #+#             */
/*   Updated: 2025/02/27 17:44:31 by najeuneh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Config.hpp"

Config::Config() {}

Config::~Config() {}

int	Config::CheckServer(int i, std::string str)
{
	size_t position;

	if ((position = str.find("host")) != std::string::npos)
		return 0;
	else if ((position = str.find("server_name")) != std::string::npos)
		return 1;
	else if ((position = str.find("client_max_body_size")) != std::string::npos)
		return 2;
	else if ((position = str.find("listen")) != std::string::npos)
		return 3;
	else if ((position = str.find("error_page")) != std::string::npos)
		return 4;
	return -1;
}

void	Config::SetServer(std::string str)
{
	std::istringstream ss;
	std::string line;
 	size_t position;

	if ((position = str.find("listen")) != std::string::npos)
	{
		ss.str(str);
		getline(ss, line, ' ');
		getline(ss, line, ';');
		this->Server.listen.push_back(line);
	}
	else if ((position = str.find("server_name")) != std::string::npos)
	{
		ss.str(str);
		getline(ss, line, ' ');
		getline(ss, line, ';');
		this->Server.server_name = line;
	}
	else if ((position = str.find("client_max_body_size")) != std::string::npos)
	{
		ss.str(str);
		getline(ss, line, ' ');
		getline(ss, line, ';');
		this->Server.client_max_body_size = line;
	}
	else if ((position = str.find("host")) != std::string::npos)
	{
		ss.str(str);
		getline(ss, line, ' ');
		std::getline(ss, line, ';');
		this->Server.host = line;
	}
	else if ((position = str.find("error_page")) != std::string::npos)
	{
		ss.str(str);
		getline(ss, line, ' ');
		getline(ss, line, ' ');
		this->Server.error_page_num = line;
		getline(ss, line, ' ');
		this->Server.error_page_loc = line;
	}

}

void	Config::SetLoc(std::string str)
{
	std::istringstream ss;
	std::string line;
 	size_t position;

	if ((position = str.find("location")) != std::string::npos)
	{
		ss.str(str);
		getline(ss, line, ' ');
		getline(ss, line, '{');
		this->Server.Loc[Server.size - 1].Location = line;
	}
	else if ((position = str.find("root")) != std::string::npos)
	{
		ss.str(str);
		getline(ss, line, ' ');
		getline(ss, line, ';');
		this->Server.Loc[Server.size - 1].root = line;
	}
	else if ((position = str.find("index ")) != std::string::npos)
	{
		ss.str(str);
		getline(ss, line, ' ');
		getline(ss, line, ';');
		std::cout << line << Server.size << std::endl;
	}
	else if ((position = str.find("redirect_url")) != std::string::npos)
	{
	}
	else if ((position = str.find("upload_store")) != std::string::npos)
	{
	}
	else if ((position = str.find("cgi_pass")) != std::string::npos)
	{
		
	}
	else if ((position = str.find("directory_listening")) != std::string::npos)
	{
	}
	else if ((position = str.find("allowed_methods")) != std::string::npos)
	{
	}
	// else if ((i = Checkword(i, str, "cgi_ext")) == 1)
		// ;
}

Config	Config::Config_file(std::string str2)
{
	Config Conf;
	std::string	str;
	std::ifstream fichier(str2.c_str());
	size_t position;

	Server.size = 1;
	while (std::getline(fichier, str, '\n'))
	{
		if (CheckServer(0, str) != -1)
		{
			SetServer(str);
		}
		else if ((position = str.find("location")) != std::string::npos)
		{
			this->Server.size++;
			this->Server.Loc.resize(Server.size);
			while (getline(fichier, str))
			{
				SetLoc(str);
				if ((position = str.find("}")) != std::string::npos)
					break ;
			}
		}
	}
	fichier.close();
	return *this;
}

int	main()
{
	Config Conf;
		
	Conf = Conf.Config_file("../example.conf");
	std::cout << "aa " << Conf.Server.server_name << std::endl;
}