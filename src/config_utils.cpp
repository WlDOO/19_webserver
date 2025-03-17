/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_utils.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:39:49 by najeuneh          #+#    #+#             */
/*   Updated: 2025/03/17 18:16:54 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Config.hpp"

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
			if (line[i] == '#')
				break ;
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

int	CheckServer_name(std::string str)
{
	int i = 0;
	
	while(str[i])
	{
		if (str[i] == '-' && i == 0)
			return 0;
		else if (str[i] == '.')
		{
			if (str[i + 1] == '.')
				return 0;
			i++;
		}
		else if(str[i] == '-')
			i++;
		else if (str[i] >= 48 && str[i] <= 57)
			i++;
		else if (str[i] >= 65 && str[i] <= 90)
			i++;
		else if (str[i] >= 97 && str[i] <= 122)
			i++;
		else
			return 0;
	}
	return 1;
}