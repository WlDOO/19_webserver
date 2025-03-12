/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najeuneh <najeuneh@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:46:38 by najeuneh          #+#    #+#             */
/*   Updated: 2025/03/11 17:44:44 by najeuneh         ###   ########.fr       */
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
	else if ((position = str.find("autoindex ")) != std::string::npos)
	{
		ss.str(str);
		getline(ss, line, ' ');
		getline(ss, line, ';');
		this->Server[size_serv].Loc[Server[size_serv].size - 1].autoindex = line;
	}
	else if ((position = str.find("upload_store ")) != std::string::npos)
	{
		ss.str(str);
		getline(ss, line, ' ');
		getline(ss, line, ';');
		this->Server[size_serv].Loc[Server[size_serv].size - 1].upload_store = line;
	}
	else if ((position = str.find("cgi_pass ")) != std::string::npos)
	{
		ss.str(str);
		getline(ss, line, ' ');
		getline(ss, line, ';');
		this->Server[size_serv].Loc[Server[size_serv].size - 1].cgi_pass.push_back(line);
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
		if ((position = str.find("GET")) != std::string::npos)
			this->Server[size_serv].Loc[Server[size_serv].size - 1].methods.push_back("GET");
		if((position = str.find("POST")) != std::string::npos)
			this->Server[size_serv].Loc[Server[size_serv].size - 1].methods.push_back("POST");
		if((position = str.find("DELETE")) != std::string::npos)
			this->Server[size_serv].Loc[Server[size_serv].size - 1].methods.push_back("DELETE");
	}
	else if ((position = str.find("cgi_ext ")) != std::string::npos)
	{
		if ((position = str.find(".py")) != std::string::npos)
			this->Server[size_serv].Loc[Server[size_serv].size - 1].cgi_extonsions.push_back(".py");
		if ((position = str.find(".php")) != std::string::npos)
			this->Server[size_serv].Loc[Server[size_serv].size - 1].cgi_extonsions.push_back(".php");
		if ((position = str.find(".sh")) != std::string::npos)
			this->Server[size_serv].Loc[Server[size_serv].size - 1].cgi_extonsions.push_back(".sh");
		if ((position = str.find(".js")) != std::string::npos)
			this->Server[size_serv].Loc[Server[size_serv].size - 1].cgi_extonsions.push_back(".js");
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
		}
	}
	return *this;
}

bool isWhitespace(char c)
{
    return (c == ' ' || (c >= 9 && c <= 13));
}

void removeExtraWhitespace(std::string& str)
{
    bool spaceFound = false;
    size_t i = 0;
    size_t j = 0;
    size_t length = str.size();
 
    if (str.empty())
		return;
    while (i < length)
	{
        if (!isWhitespace(str[i]))
		{
            str[j++] = str[i++];
            spaceFound = false;
        }
        else if (isWhitespace(str[i]))
		{
            if (i != length)
			{
                if (!spaceFound)
				{
                    str[j++] = ' ';
                    spaceFound = true;
                }
            }
            i++;
        }
    }
    if (j > 0 && isWhitespace(str[length - 1]))
        str[j++] = str[length - 1];
    str.resize(j);
}

std::string	pick_file(std::string str)
{
	std::string line;
	std::string res;
	std::ifstream file(str.c_str());
	
	while (getline(file, line))
	{
		int i = 0;
		int y = 0;
		while(line[i] && (line[i] == 32 || (line[i] >= 9 && line[i] <= 13)))
			i++;
		y = i;
		while(line[i])
		{
			if(line[i] == ';' || line[i] == '{' || line[i] == '}')
			{
				if (y == 0)
					line = line.substr(y, i + 1);
				else
					line = line.substr(y, i);
				removeExtraWhitespace(line);
				line.append("\n");
				res.append(line);
				break ;
			}
			else
			i++;
		}
	}
	return res;
}

bool isDirectory(const std::string& path)
{
	struct stat info;

	if (path.empty())
		return true;
	if (stat(path.c_str(), &info) != 0)
		return false;
	else if (info.st_mode & S_IFDIR)
		return true;
	else if (open(path.c_str(), R_OK) != -1)
		return true;
	return false;
}

bool	isIp(std::string ip)
{
	int point = 0;
	int value;
	for (int i = 0; ip[i]; i++)
	{
		if (isalpha(ip[i]))
			return false;
		if (ip[i] == '.')
			point++;
	}
	if (point != 3)
		return false;
	point = 0;
	for (int i = 0; ip[i]; i++)
	{
		if (ip[i] == '.')
		{
			if (point == 0)
				value = atoi(ip.substr(point, i).c_str());
			else
				value = atoi(ip.substr(point + 1, ((i - 1) - point)).c_str());
			if (value == 0)
			{
				if (ip.substr(point, i) != "0")
					value = -1;
			}
			point = i;
		}
		else if (ip[i + 1] == '\0' && (atoi(ip.substr(point + 1, i - point).c_str()) > 255 || atoi(ip.substr(point + 1, i - point).c_str()) < 0))
			return false;
	}
	return true;
}

int	parse_file(Config Conf)
{
	for (size_t i = 0; i < Conf.Server.size(); i++)
	{
		if (Conf.Server[i].root.empty() || Conf.Server[i].server_name.empty() || Conf.Server[i].listen.size() == 0 || Conf.Server[i].Loc.size() == 0)
			return std::cerr << "Error: Missing information in server block" << std::endl, 0;
		if (!isDirectory(Conf.Server[i].root))
			return std::cerr << "Error: Root directory does not exist" << std::endl, 0;
		for (size_t y = 0; y < Conf.Server[i].error_page_loc.size(); y++)
		{
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
			if (!isDirectory(Conf.Server[i].Loc[y].index))
				return std::cerr << "Error: Error page index directory does not exist" << std::endl, 0;
			if (!isDirectory(Conf.Server[i].Loc[y].redirect_url))
				return std::cerr << "Error: Error page redirect url directory does not exist" << std::endl, 0;
			if (!isDirectory(Conf.Server[i].Loc[y].upload_store))
				return std::cerr << "Error: Error page upload store directory does not exist" << std::endl ,0;
			for (size_t x = 0; x < Conf.Server[i].Loc.size(); x++)
			{
				if (!isDirectory(Conf.Server[i].Loc[y].cgi_pass[x]))
					return std::cerr << "Error: Error page Localisation directory does not exist" << std::endl, 0;
			}
			for (size_t x = 0; x < Conf.Server[i].Loc[y].methods.size(); x++)
			{
				if (Conf.Server[i].Loc[y].methods[x] != "GET" || Conf.Server[i].Loc[y].methods[x] != "POST" || Conf.Server[i].Loc[y].methods[x] != "DELETE")
					return std::cerr << "Error: allow method does not exist" << std::endl, 0;
			}
			for (size_t x = 0; x < Conf.Server[i].Loc[y].cgi_extonsions.size(); x++)
			{
				if (Conf.Server[i].Loc[y].methods[x] != ".py" || Conf.Server[i].Loc[y].methods[x] != ".js" || Conf.Server[i].Loc[y].methods[x] != ".sh")
					return std::cerr << "Error: allow method does not exist" << std::endl, 0;
			}
		}
	}
	return 1;
}

int	main()
{
	Config Conf;
	std::string str = "../example.conf";
	std::string str2 = pick_file(str);
	Conf = Conf.Config_file(str2);
	if (parse_file(Conf) == 0)
		return 0;

	return 0;
}