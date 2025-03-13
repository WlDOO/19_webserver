/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najeuneh <najeuneh@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:46:38 by najeuneh          #+#    #+#             */
/*   Updated: 2025/03/13 16:41:01 by najeuneh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Config.hpp"

Config::Config() {}

Config::~Config() {}

int	Config::CheckServer(std::string str)
{
	size_t position;

	if ((position = str.find("host ")) != std::string::npos)
		return 0;
	else if ((position = str.find("server_name ")) != std::string::npos)
		return 1;
	else if ((position = str.find("client_max_body_size ")) != std::string::npos)
		return 2;
	else if ((position = str.find("listen ")) != std::string::npos)
		return 3;
	else if ((position = str.find("error_page ")) != std::string::npos)
		return 4;
	else if ((position = str.find("root ")) != std::string::npos)
		return 5;
	return -1;
}

void	Config::SetServer(std::string str)
{
	std::istringstream ss;
	std::string line;
 	size_t position;

	if ((position = str.find("listen ")) != std::string::npos)
	{
		ss.str(str);
		getline(ss, line, ' ');
		getline(ss, line, ';');
		this->Server[size_serv].listen.push_back(line);
	}
	else if ((position = str.find("server_name ")) != std::string::npos)
	{
		ss.str(str);
		getline(ss, line, ' ');
		getline(ss, line, ';');
		this->Server[size_serv].server_name = line;
	}
	else if ((position = str.find("client_max_body_size ")) != std::string::npos)
	{
		ss.str(str);
		getline(ss, line, ' ');
		getline(ss, line, ';');
		this->Server[size_serv].client_max_body_size = line;
	}
	else if ((position = str.find("host ")) != std::string::npos)
	{
		ss.str(str);
		getline(ss, line, ' ');
		std::getline(ss, line, ';');
		this->Server[size_serv].host = line;
	}
	else if ((position = str.find("error_page ")) != std::string::npos)
	{
		std::cout << str << std::endl;
		ss.str(str);
		getline(ss, line, ' ');
		getline(ss, line, ' ');
		this->Server[size_serv].error_page_num.push_back(line);
		getline(ss, line, ';');
		this->Server[size_serv].error_page_loc.push_back(line);
	}
	else if ((position = str.find("root ")) != std::string::npos)
	{
		ss.str(str);
		getline(ss, line, ' ');
		getline(ss, line, ';');
		this->Server[size_serv].root = line;
	}
}

void	Config::SetLoc(std::string str)
{
	std::istringstream ss;
	std::string line;
 	size_t position;

	if ((position = str.find("location ")) != std::string::npos)
	{
		ss.str(str);
		getline(ss, line, ' ');
		getline(ss, line, '{');
		position = line.find(" ");
		this->Server[size_serv].Loc[Server[size_serv].size - 1].Location = line.substr(0, position);
	}
	else if ((position = str.find("root ")) != std::string::npos)
	{
		ss.str(str);
		getline(ss, line, ' ');
		getline(ss, line, ';');
		this->Server[size_serv].Loc[Server[size_serv].size - 1].root = line;
	}
	else if ((position = str.find("autoindex ")) != std::string::npos)
	{
		ss.str(str);
		getline(ss, line, ' ');
		getline(ss, line, ';');
		this->Server[size_serv].Loc[Server[size_serv].size - 1].autoindex = line;
	}
	else if ((position = str.find("index ")) != std::string::npos)
	{
		
		ss.str(str);
		getline(ss, line, ' ');
		getline(ss, line, ';');
		this->Server[size_serv].Loc[Server[size_serv].size - 1].index = line;
	}
	else if ((position = str.find("return ")) != std::string::npos)
	{
		ss.str(str);
		getline(ss, line, ' ');
		getline(ss, line, ';');
		this->Server[size_serv].Loc[Server[size_serv].size - 1].redirect_url = line;
	}
	else if ((position = str.find("upload_store ")) != std::string::npos)
	{
		ss.str(str);
		getline(ss, line, ' ');
		getline(ss, line, ';');
		this->Server[size_serv].Loc[Server[size_serv].size - 1].upload_store = line;
	}
	else if ((position = str.find("cgi_path ")) != std::string::npos)
	{
		int last_pos = 0;
		ss.str(str);
		getline(ss, line, ' ');
		getline(ss, line, ';');
		for (int y = 0; line[y]; y++)
		{
			if (line[y] == ' ' || line[y + 1] == '\0')
			{
				if (last_pos == 0)
					this->Server[size_serv].Loc[Server[size_serv].size - 1].cgi_pass.push_back(line.substr(last_pos, y));
				else if (line[y + 1] == '\0')
					this->Server[size_serv].Loc[Server[size_serv].size - 1].cgi_pass.push_back(line.substr(last_pos + 1, y - last_pos + 1));
				else
					this->Server[size_serv].Loc[Server[size_serv].size - 1].cgi_pass.push_back(line.substr(last_pos + 1, y - last_pos - 1));
				last_pos = y;
			}
		}
	}
	else if ((position = str.find("directory_listening ")) != std::string::npos)
	{
		ss.str(str);
		getline(ss, line, ' ');
		getline(ss, line, ';');
		this->Server[size_serv].Loc[Server[size_serv].size - 1].directory_listening = line;
	}
	else if ((position = str.find("allow_methods ")) != std::string::npos)
	{
		int last_pos = 0;
		ss.str(str);
		getline(ss, line, ' ');
		getline(ss, line, ';');
		for (int y = 0; line[y]; y++)
		{
			if (line[y] == ' ' || line[y + 1] == '\0')
			{
				if (last_pos == 0)
					this->Server[size_serv].Loc[Server[size_serv].size - 1].methods.push_back(line.substr(last_pos, y));
				else
					this->Server[size_serv].Loc[Server[size_serv].size - 1].methods.push_back(line.substr(last_pos + 1, y - last_pos));
				last_pos = y;
			}
		}
	}
	else if ((position = str.find("cgi_ext ")) != std::string::npos)
	{
		int last_pos = 0;
		ss.str(str);
		getline(ss, line, ' ');
		getline(ss, line, ';');
		for (int y = 0; line[y]; y++)
		{
			if (line[y] == ' ' || line[y + 1] == '\0')
			{
				if (last_pos == 0)
					this->Server[size_serv].Loc[Server[size_serv].size - 1].cgi_extonsions.push_back(line.substr(last_pos, y));
				else if (line[y + 1] == '\0')
					this->Server[size_serv].Loc[Server[size_serv].size - 1].cgi_extonsions.push_back(line.substr(last_pos + 1, y - last_pos + 1));
				else
					this->Server[size_serv].Loc[Server[size_serv].size - 1].cgi_extonsions.push_back(line.substr(last_pos + 1, y - last_pos - 1));
				last_pos = y;
			}
		}
	}
}

Config	Config::Config_file(std::string str2)
{
	Config Conf;
	std::string	str;
	std::istringstream fichier;
	fichier.str(str2);
	size_t position;

	size_serv = -1;
	while (std::getline(fichier, str, '\n'))
	{
		if  ((position = str.find("server")) != std::string::npos && (position = str.find("{")) != std::string::npos)
		{
			size_serv++;
			this->Server.resize(size_serv + 1);
			Server[size_serv].size = 0;
		}
		else if (CheckServer(str) != -1)
			SetServer(str);
		else if ((position = str.find("location ")) != std::string::npos)
		{
			this->Server[size_serv].size++;
			this->Server[size_serv].Loc.resize(Server[size_serv].size);
			SetLoc(str);
			while (getline(fichier, str))
			{
				SetLoc(str);
				if ((position = str.find("}")) != std::string::npos)
					break ;
			}
			if (this->Server[size_serv].Loc[Server[size_serv].size - 1].root.empty())
				this->Server[size_serv].Loc[Server[size_serv].size - 1].root = this->Server[size_serv].root;
		}
	}
	return *this;
}

int	parse_file(Config Conf)
{
	for (size_t i = 0; i < Conf.Server.size(); i++)
	{
		if (CheckServer_name(Conf.Server[i].server_name) == 0)
			return std::cerr << "Error: Server name is not good" << std::endl, 0;
		if (Conf.Server[i].root.empty() || Conf.Server[i].server_name.empty() || Conf.Server[i].listen.size() == 0 || Conf.Server[i].Loc.size() == 0)
			return std::cerr << "Error: Missing information in server block" << std::endl, 0;
		if (!isDirectory(Conf.Server[i].root))
			return std::cerr << "Error: Root directory does not exist" << std::endl, 0;
		for (size_t y = 0; y < Conf.Server[i].error_page_loc.size(); y++)
		{
			std::cout << Conf.Server[i].error_page_loc[y] << std::endl;
			if (!isDirectory(Conf.Server[i].error_page_loc[y]))
				return std::cerr << "Error: Error page Localisation directory does not exist" << std::endl, 0;
			if (atoi(Conf.Server[i].error_page_num[y].c_str()) < 100 || atoi(Conf.Server[i].error_page_num[y].c_str()) > 599)
				return std::cerr << "Error: Error page number does not exist" << std::endl, 0;
		}
		if (!isIp(Conf.Server[i].host))
			return std::cerr << "Error: host does not exist" << std::endl, 0;
		for (size_t y = 0; y < Conf.Server[i].listen.size(); y++)
		{
			if (atoi(Conf.Server[i].listen[y].c_str()) < 1024 || atoi(Conf.Server[i].listen[y].c_str()) > 65535)
				return std::cerr << "Error: listen does not possible" << std::endl, 0;
		}
		if (atoi(Conf.Server[i].client_max_body_size.c_str()) < 0 || atoi(Conf.Server[i].client_max_body_size.c_str()) > (10 * 1024 * 1024))
			return std::cerr << "Error: client mac body size does not goot" << std::endl, 0;
		for (size_t y = 0; y < Conf.Server[i].Loc.size(); y++)
		{
			if (!isDirectory(Conf.Server[i].Loc[y].Location))
				return std::cerr << "Error: Error page Localisation directory does not exist" << std::endl, 0;
			if (!isDirectory(Conf.Server[i].Loc[y].root))
				return std::cerr << "Error: Error page root directory does not exist" << std::endl, 0;
			if (!isDirectory(Conf.Server[i].Loc[y].redirect_url))
				return std::cerr << "Error: Error page redirect url directory does not exist" << std::endl, 0;
			if (!isDirectory(Conf.Server[i].Loc[y].upload_store))
				return std::cerr << "Error: Error page upload store directory does not exist" << std::endl ,0;
			if (!Conf.Server[i].Loc[y].autoindex.empty() && Conf.Server[i].Loc[y].autoindex != "on" && Conf.Server[i].Loc[y].autoindex != "off")
				return std::cerr << "Error: Error autoindex  does not exist" << std::endl, 0;
			for (size_t x = 0; x < Conf.Server[i].Loc[y].cgi_pass.size(); x++)
			{
				if (!isDirectory(Conf.Server[i].Loc[y].cgi_pass[x]))
					return std::cerr << "Error: Error page cgi pass directory does not exist" << std::endl, 0;
			}
			for (size_t x = 0; x < Conf.Server[i].Loc[y].methods.size(); x++)
			{
				if (Conf.Server[i].Loc[y].methods[x] != "GET" && Conf.Server[i].Loc[y].methods[x] != "POST" && Conf.Server[i].Loc[y].methods[x] != "DELETE")
					return std::cerr << "Error: allow method does not exist" << std::endl, 0;
			}
			for (size_t x = 0; x < Conf.Server[i].Loc[y].cgi_extonsions.size(); x++)
			{
				if (Conf.Server[i].Loc[y].cgi_extonsions[x] != ".py" && Conf.Server[i].Loc[y].cgi_extonsions[x] != ".js" && Conf.Server[i].Loc[y].cgi_extonsions[x] != ".sh")
					return std::cerr << "Error: cgi extension does not exist" << std::endl, 0;
			}
		}
	}
	return 1;
}

int	main()
{
	Config Conf;
	std::string str = "example.conf";
	std::string str2 = pick_file(str);
	Conf = Conf.Config_file(str2);
	if (parse_file(Conf) == 0)
		return 0;
	return 0;
}