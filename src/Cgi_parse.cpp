/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi_parse.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 14:01:47 by armitite          #+#    #+#             */
/*   Updated: 2025/04/10 16:06:59 by armitite         ###   ########.fr       */
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
	if (found == std::string::npos)
		return (1);
	Content_type = output.substr(0, found);
	if (found == std::string::npos)
		return (1);
	output.erase(0, found + 8);
	_Cgi_output = output;
	
	return (0);
}