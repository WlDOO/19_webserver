/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse_request.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:35:41 by armitite          #+#    #+#             */
/*   Updated: 2025/03/18 17:39:04 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

int		Server::check_cgi(void) {

	std::size_t found;
	std::string ext;
	std::string ext_tmp;
	
	ext_tmp = ".py";
	found = _Request_content.rfind(".");
	ext = _Request_content.substr(found, _Request_content.size() - found);
	std::cout << "ext_tmp : " << ext_tmp << std::endl;
	std::cout << "ext : " << ext << std::endl;
	if (ext != ext_tmp)
		return (1);
	
	return (0);
}

int		Server::check_vectors(std::vector<std::string> vector, std::string to_find) {
	
	size_t i;
	
	for (i = 0; i < vector.size(); i++) {

		//std::cout << vector[i] << std::endl;
		if (to_find == vector[i])
		{
			std::cout << "ok" << std::endl;
			return (1);
		}
	}

	return (0);
}

int		Server::parse_request(void) {

	size_t found;
	std::string loc;
	std::vector<std::string> myloc;
	std::vector<std::string> methods;
	
	myloc.push_back("test");
	myloc.push_back("alo");
	myloc.push_back("post");
	myloc.push_back("cgi-bin");
	found = _Request_content.find("/");
	if (found == std::string::npos)
		return (1);
	loc = _Request_content.substr(0, found);
	if (check_vectors(myloc, loc) != 1)
		return (print_logs("Client", "Location not found", 2), 404);
	std::cout << "la loc :" << loc << std::endl;
	if (loc == "cgi-bin")
		check_cgi();
	//if (autoindex == "on") a faire
	methods.push_back("GET");
	methods.push_back("POST");
	if (check_vectors(methods, _Request_type) != 1)
		return (print_logs("Client", "Unothorized method", 2), 404);

	return (0);
}