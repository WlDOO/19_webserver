/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse_request.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:35:41 by armitite          #+#    #+#             */
/*   Updated: 2025/03/18 15:11:00 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

int		Server::parse_request(void) {

	size_t found;
	std::string loc;
	size_t i;
	std::vector<std::string> myloc;
	std::vector<std::string> methods;
	
	myloc.push_back("test");
	myloc.push_back("alo");
	myloc.push_back("post");
	found = _Request_content.find("/");
	if (found == std::string::npos)
		return (1);
	loc = _Request_content.substr(0, found);
	for (i = 0; i < myloc.size(); i++) {

		std::cout << myloc[i] << std::endl;
		if (loc == myloc[i])
		{
			break ;
		}
	}
	if (i == myloc.size())
		return (404);
	std::cout << loc << std::endl;
	//if (autoindex == "on") a faire
	methods.push_back("GET");
	methods.push_back("POST");
	for (i = 0; i < methods.size(); i++) {

		std::cout << methods[i] << std::endl;
		if (_Request_type == methods[i])
		{
			break ;
		}
	}

	return (0);
}