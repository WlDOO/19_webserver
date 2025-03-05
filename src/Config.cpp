/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najeuneh <najeuneh@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:46:38 by najeuneh          #+#    #+#             */
/*   Updated: 2025/03/05 17:58:44 by najeuneh         ###   ########.fr       */
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
		this->Server[size_serv].error_page_num = line;
		getline(ss, line, ';');
		this->Server[size_serv].error_page_loc = line;
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
		this->Server[size_serv].Loc[Server[size_serv].size - 1].Location = line;
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
		this->Server[size_serv].Loc[Server[size_serv].size - 1].cgi_pass = line;
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

Config	parse_file(Config Conf, std::string str)
{
	std::fstream fs;
	
	fs.open(str.c_str());
	if (!fs.is_open())
	{
		std::cerr << "Error: " << strerror(errno) << std::endl;
		return Conf;
	}
	std::string str2 = pick_file(str);
	Conf.Config_file(str2);
	return Conf;
}	

int	main()
{
	Config Conf;
	Conf = parse_file(Conf, "config.conf");
	return 0;
}