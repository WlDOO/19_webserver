/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi_parse.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 14:01:47 by armitite          #+#    #+#             */
/*   Updated: 2025/03/21 14:54:19 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

int		Server::cgi_parse(std::string output) {

	size_t found;
	std::string Content_type;
	
	found = output.find("Content-Type:", 0);
	if (found == std::string::npos)
		return (1);
	output.erase(0, found + 8);
	found = output.find("\r\n");
	Content_type = output.substr(0, found);
	std::cout << output << " sad " << std::endl;
	std::cout << Content_type << std::endl;
	if (found == std::string::npos)
	{
		std::cout << "found pb" << std::endl;
		return (1);
	}
	std::cout << "found cgi parse : " << found << std::endl;
	output.erase(0, found + 8);
	_Cgi_output = output;
	std::cout << "Le cgi ouput : "<< _Cgi_output << std::endl;
	
	
	return (0);
}