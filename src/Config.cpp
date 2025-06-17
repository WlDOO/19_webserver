/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najeuneh <najeuneh@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:46:38 by najeuneh          #+#    #+#             */
/*   Updated: 2025/06/17 15:08:27 by najeuneh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Config.hpp"

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
	else if ((position = str.find("index ")) != std::string::npos)
		return 6;
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
		this->Server_par[size_serv].listen.push_back(line);
	}
	else if ((position = str.find("server_name ")) != std::string::npos)
	{
		ss.str(str);
		getline(ss, line, ' ');
		getline(ss, line, ';');
		this->Server_par[size_serv].server_name = line;
	}
	else if ((position = str.find("client_max_body_size ")) != std::string::npos)
	{
		ss.str(str);
		getline(ss, line, ' ');
		getline(ss, line, ';');
		this->Server_par[size_serv].client_max_body_size = line;
	}
	else if ((position = str.find("host ")) != std::string::npos)
	{
		ss.str(str);
		getline(ss, line, ' ');
		std::getline(ss, line, ';');
		this->Server_par[size_serv].host = line;
	}
	else if ((position = str.find("error_page ")) != std::string::npos)
	{
		ss.str(str);
		getline(ss, line, ' ');
		getline(ss, line, ' ');
		this->Server_par[size_serv].error_page_num.push_back(line);
		getline(ss, line, ';');
		this->Server_par[size_serv].error_page_loc.push_back(line);
	}
	else if ((position = str.find("root ")) != std::string::npos)
	{
		ss.str(str);
		getline(ss, line, ' ');
		getline(ss, line, ';');
		if (line[line.size() - 1] != '/')
			line.append("/");
		this->Server_par[size_serv].root = line;
	}
	else if ((position = str.find("index ")) != std::string::npos)
	{
		ss.str(str);
		getline(ss, line, ' ');
		getline(ss, line, ';');
		this->Server_par[size_serv].index = line;
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
		if (line[line.size() - 1 == ' '])
		line.erase(line.size() - 1);
		this->Server_par[size_serv].Loc[Server_par[size_serv].size - 1].Location = line;
	}
	else if ((position = str.find("root ")) != std::string::npos)
	{
		ss.str(str);
		getline(ss, line, ' ');
		getline(ss, line, ';');
		if (line[line.size() - 1] != '/')
			line.append("/");
		this->Server_par[size_serv].Loc[Server_par[size_serv].size - 1].root = line;
	}
	else if ((position = str.find("alias ")) != std::string::npos)
	{
		ss.str(str);
		getline(ss, line, ' ');
		getline(ss, line, ';');
		if (line[line.size() - 1] != '/')
			line.append("/");
		this->Server_par[size_serv].Loc[Server_par[size_serv].size - 1].alias = line;
	}
	else if ((position = str.find("autoindex ")) != std::string::npos)
	{
		ss.str(str);
		getline(ss, line, ' ');
		getline(ss, line, ';');
		this->Server_par[size_serv].Loc[Server_par[size_serv].size - 1].autoindex = line;
	}
	else if ((position = str.find("index ")) != std::string::npos)
	{
		
		ss.str(str);
		getline(ss, line, ' ');
		getline(ss, line, ';');
		this->Server_par[size_serv].Loc[Server_par[size_serv].size - 1].index = line;
	}
	else if ((position = str.find("return ")) != std::string::npos)
	{
		ss.str(str);
		getline(ss, line, ' ');
		getline(ss, line, ';');
		this->Server_par[size_serv].Loc[Server_par[size_serv].size - 1].redirect_url = line;
	}
	else if ((position = str.find("upload_store ")) != std::string::npos)
	{
		ss.str(str);
		getline(ss, line, ' ');
		getline(ss, line, ';');
		this->Server_par[size_serv].Loc[Server_par[size_serv].size - 1].upload_store = line;
	}
	else if ((position = str.find("script ")) != std::string::npos)
	{
		ss.str(str);
		getline(ss, line, ' ');
		getline(ss, line, ';');
		this->Server_par[size_serv].Loc[Server_par[size_serv].size - 1].script = line;
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
				{
					if (line[y + 1] == '\0')
						this->Server_par[size_serv].Loc[Server_par[size_serv].size - 1].cgi_pass = line.substr(last_pos, y - last_pos + 1);
					else
					this->Server_par[size_serv].Loc[Server_par[size_serv].size - 1].cgi_pass = line.substr(last_pos, y);
				}
				else if (line[y + 1] == '\0')
					this->Server_par[size_serv].Loc[Server_par[size_serv].size - 1].cgi_pass = line.substr(last_pos + 1, y - last_pos + 1);
				else
					this->Server_par[size_serv].Loc[Server_par[size_serv].size - 1].cgi_pass = line.substr(last_pos + 1, y - last_pos - 1);
				last_pos = y;
			}
		}
	}
	else if ((position = str.find("directory_listening ")) != std::string::npos)
	{
		ss.str(str);
		getline(ss, line, ' ');
		getline(ss, line, ';');
		this->Server_par[size_serv].Loc[Server_par[size_serv].size - 1].directory_listening = line;
	}
	else if ((position = str.find("allow_methods ")) != std::string::npos)
	{
		int last_pos = 0;
		int index = 0;
		ss.str(str);
		getline(ss, line, ' ');
		getline(ss, line, ';');
		for (int y = 0; line[y]; y++)
		{
			if (line[y] == ' ' || line[y + 1] == '\0')
			{
				if (line[y + 1] == '\0')
				{
					if (last_pos == 0)
						this->Server_par[size_serv].Loc[Server_par[size_serv].size - 1].methods.push_back(line.substr(last_pos, y - last_pos + 1));
					else
						this->Server_par[size_serv].Loc[Server_par[size_serv].size - 1].methods.push_back(line.substr(last_pos + 1, y - last_pos));
				}
				else
					this->Server_par[size_serv].Loc[Server_par[size_serv].size - 1].methods.push_back(line.substr(last_pos, y - last_pos));
				last_pos = y;
				for (size_t i = 0; i < this->Server_par[size_serv].Loc[Server_par[size_serv].size - 1].methods[index].length(); ) {
					if (this->Server_par[size_serv].Loc[Server_par[size_serv].size - 1].methods[index][i] == ' ')
						this->Server_par[size_serv].Loc[Server_par[size_serv].size - 1].methods[index].erase(i, 1);
					else
						++i;
				}
				index++;
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
				{
					if (line[y + 1] == '\0')
						this->Server_par[size_serv].Loc[Server_par[size_serv].size - 1].cgi_extonsions = line.substr(last_pos, y - last_pos + 1);
					else
						this->Server_par[size_serv].Loc[Server_par[size_serv].size - 1].cgi_extonsions = line.substr(last_pos, y);
				}
					else if (line[y + 1] == '\0')
					this->Server_par[size_serv].Loc[Server_par[size_serv].size - 1].cgi_extonsions = line.substr(last_pos + 1, y - last_pos + 1);
				else
					this->Server_par[size_serv].Loc[Server_par[size_serv].size - 1].cgi_extonsions = line.substr(last_pos + 1, y - last_pos - 1);
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
			this->Server_par.resize(size_serv + 1);
			Server_par[size_serv].size = 0;
		}
		else if (CheckServer(str) != -1)
			SetServer(str);
		else if ((position = str.find("location ")) != std::string::npos)
		{
			this->Server_par[size_serv].size++;
			this->Server_par[size_serv].Loc.resize(Server_par[size_serv].size);
			SetLoc(str);
			while (getline(fichier, str))
			{
				SetLoc(str);
				if ((position = str.find("}")) != std::string::npos)
					break ;
			}
			if (this->Server_par[size_serv].Loc[Server_par[size_serv].size - 1].root.empty())
				this->Server_par[size_serv].Loc[Server_par[size_serv].size - 1].root = this->Server_par[size_serv].root;
		}
	}
	*this = setpath(*this);
	return *this;
}

int	parse_file(Config Conf)
{
	for (size_t i = 0; i < Conf.Server_par.size(); i++)
	{
		if (CheckServer_name(Conf.Server_par[i].server_name) == 0)
			return std::cerr << "Error: Server_par name is not good" << std::endl, 0;
		if (Conf.Server_par[i].index.empty() || Conf.Server_par[i].root.empty() || Conf.Server_par[i].server_name.empty() || Conf.Server_par[i].listen.size() == 0 || Conf.Server_par[i].Loc.size() == 0)
			return std::cerr << "Error: Missing information in server block" << std::endl, 0;
		if (!isDirectory(Conf.Server_par[i].root)) {
			std::cout << Conf.Server_par[i].root << std::endl;
			return std::cerr << "Error: Root directory does not exist" << std::endl, 0;
		}
		if (!isDirectory(Conf.Server_par[i].index)) {
			return std::cerr << "Error: index directory does not exist" << std::endl, 0;
		}
			for (size_t y = 0; y < Conf.Server_par[i].error_page_loc.size(); y++)
		{
			if (!isDirectory(Conf.Server_par[i].error_page_loc[y]))

				return std::cerr << "Error: Error page Localisation directory does not exist" << std::endl, 0;
			if (atoi(Conf.Server_par[i].error_page_num[y].c_str()) < 100 || atoi(Conf.Server_par[i].error_page_num[y].c_str()) > 599)
				return std::cerr << "Error: Error page number does not exist" << std::endl, 0;
		}
		if (!isIp(Conf.Server_par[i].host))
			return std::cerr << "Error: host does not exist" << std::endl, 0;
		for (size_t y = 0; y < Conf.Server_par[i].listen.size(); y++)
		{
			if (atoi(Conf.Server_par[i].listen[y].c_str()) < 1024 || atoi(Conf.Server_par[i].listen[y].c_str()) > 65535)
				return std::cerr << "Error: listen does not possible" << std::endl, 0;
		}
		if (atoi(Conf.Server_par[i].client_max_body_size.c_str()) < 0 || atoi(Conf.Server_par[i].client_max_body_size.c_str()) > (10 * 1024 * 1024))
			return std::cerr << "Error: client mac body size does not goot" << std::endl, 0;
		for (size_t y = 0; y < Conf.Server_par[i].Loc.size(); y++)
		{
			for (size_t x = 0; x < y; x++)
			{
				if (Conf.Server_par[i].Loc[y].Location == Conf.Server_par[i].Loc[x].Location)
				{
					return std::cerr << "Error: Location is not unique" << std::endl, 0;
				}
			}
			if (!isDirectory(Conf.Server_par[i].Loc[y].Location))
			{
				std::cout << "ici" << Conf.Server_par[i].Loc[y].Location << "ici" << std::endl;
				return std::cerr << "Error: Error page Localisation directory does not exist" << std::endl, 0;
			}
				if (!isDirectory(Conf.Server_par[i].Loc[y].root))
				return std::cerr << "Error: Error page root directory does not exist" << std::endl, 0;
			if (!isDirectory(Conf.Server_par[i].Loc[y].redirect_url))
			{
				std::cout << Conf.Server_par[i].Loc[y].redirect_url << std::endl;
				return std::cerr << "Error: Error page redirect url directory does not exist" << std::endl, 0;
			}
			if (!isDirectory(Conf.Server_par[i].Loc[y].upload_store))
				return std::cerr << "Error: Error page upload store directory does not exist" << std::endl, 0;
			if (!Conf.Server_par[i].Loc[y].autoindex.empty() && Conf.Server_par[i].Loc[y].autoindex != "on" && Conf.Server_par[i].Loc[y].autoindex != "off")
				return std::cerr << "Error: Error autoindex  does not exist" << std::endl, 0;
			if (Conf.Server_par[i].Loc[y].autoindex == "off" && Conf.Server_par[i].Loc[y].index.empty())
				return std::cerr << "Error: Error index  does not exist" << std::endl, 0;
			else if (!isDirectory(Conf.Server_par[i].Loc[y].index))
				return std::cerr << "Error: Error index  does not exist" << std::endl, 0;
			if (!isDirectory(Conf.Server_par[i].Loc[y].alias))
					return std::cerr << "Error: Error alias does not exist" << std::endl, 0;			
			if (!isDirectory(Conf.Server_par[i].Loc[y].script))
					return std::cerr << "Error: Error script does not exist" << std::endl, 0;
			if (!isDirectory(Conf.Server_par[i].Loc[y].cgi_pass))
				return std::cerr << "Error: Error page cgi pass directory does not exist" << std::endl, 0;
			for (size_t x = 0; x < Conf.Server_par[i].Loc[y].methods.size(); x++)
			{
				if (Conf.Server_par[i].Loc[y].methods[x] != "GET" && Conf.Server_par[i].Loc[y].methods[x] != "POST" && Conf.Server_par[i].Loc[y].methods[x] != "DELETE")
				{
					return std::cerr << "Error: allow method does not exist" << std::endl, 0;
				}
			}
			std::cout << std::endl;
			if (!Conf.Server_par[i].Loc[y].cgi_extonsions.empty() && Conf.Server_par[i].Loc[y].cgi_extonsions != ".py" && Conf.Server_par[i].Loc[y].cgi_extonsions != ".js" && Conf.Server_par[i].Loc[y].cgi_extonsions != ".sh")
				return std::cerr << "Error: cgi extension does not exist" << std::endl, 0;
		}
	}
	return 1;
}