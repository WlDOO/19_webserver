/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najeuneh <najeuneh@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:46:38 by najeuneh          #+#    #+#             */
/*   Updated: 2025/02/24 18:23:11 by najeuneh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Config.hpp"

Config::Config() {}

Config::~Config() {}

std::string	GetLoc(int i, int y)
{}

int	Checkword(int i, std::string str, std::string word)
{
	int y = 0;
	while(str[i])
	{
		if (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
			i++;
		else if (str[i] >= 97 && str[i] <= 122)
		{
			while (str[i] == word[y])
			{
				i++;
				y++;
				if (word[y] == '\0')
					return 1;
			}
			return 0;
		}
	}
}

int	Config::CheckServer(int i, std::string str)
{
	if (Checkword(i, str, "host") == 1)
		return 0;
	else if (Checkword(i, str, "server_name") == 1)
		return 1;
	else if (Checkword(i, str, "client_max_body_size") == 1)
		return 2;
	else if (Checkword(i, str, "listen") == 1)
		return 3;
	else if (Checkword(i, str, "error_page") == 1)
		return 4;
	return -1;
}

int	Config::CheckLoc(int i, std::string str)
{
	if (Checkword(i, str, "location") == 1)
		return 0;
	else if (Checkword(i, str, "root") == 1)
		return 1;
	else if (Checkword(i, str, "index") == 1)
		return 2;
	else if (Checkword(i, str, "redirect_url") == 1)
		return 3;
	else if (Checkword(i, str, "upload_store") == 1)
		return 4;
	else if (Checkword(i, str, "cgi_pass") == 1)
		return 5;
	else if (Checkword(i, str, "directory_listening") == 1)
		return 6;
	else if (Checkword(i, str, "allowed_methods") == 1)
		return 7;
	else if (Checkword(i, str, "cgi_extonsions") == 1)
		return 8;
	return -1;
}

int	Config::NextLigne(int i, std::string str)
{
	while (str[i])
	{
		i++;
		if (str[i] == '\n')
			return i;
	}
	return i;
}

Config	Config::Config_file(int fd)
{
	Config Conf;
	std::string	str;
	int y;
	char buffer[4096];
	int	bs;
	while(bs = read(fd, buffer, sizeof(buffer)) > 0)
		str.append(buffer, bs);
	for (int i = 0; str[i]; i++)
	{
		if (y = CheckServer(i, str) != -1)
		{
			
		}
		else if (y = CheckLoc(i, str) != -1)
		{
			
		}
		i = NextLigne(i, str);
	}
}