/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Set_request.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:56:53 by armitite          #+#    #+#             */
/*   Updated: 2025/04/10 14:21:58 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

int	Server::set_request_http(std::string full_msg) {

	std::string verbs;
	size_t	found;
	
	found = full_msg.find("HTTP/1.1", 0);
	if (found == std::string::npos)
		return (print_logs("Client", "Incorrect content format", 2), 400);
	verbs = full_msg.substr(0, found);
	found = verbs.find(" ", 0);
	if (found == std::string::npos)
		return (print_logs("Client", "Incorrect content format", 2), 400);
	_Request_type = verbs.substr(0, found);
	if (_Request_type != "GET" && _Request_type != "POST") 
		return (print_logs("Client", "Unsupported method: " + _Request_type, 2), 405);
	std::cout << "Request type: " << _Request_type << std::endl;
	verbs.erase(0, found);
	_Request_content = verbs.substr(2, (verbs.size() - 3));
	
	return (0);
}

int	Server::set_request_type(char buffer[BUFSIZ]) {

	std::ostringstream oss_tmp;
	std::string sender_msg;
	std::string full_msg;
	std::string verbs;
	size_t del_method;
	int		error;
	
	_Http_code = 0;
	_Is_autoindex = 0;
	_Is_cgi = 0;
	error = 0;
	oss_tmp << buffer;
	sender_msg = oss_tmp.str();
	full_msg.assign(sender_msg);
	if (full_msg.find("favicon.ico") != std::string::npos)
		return (0);
	std::cout << " full_msg is : " << full_msg << std::endl;
	error = set_request_http(full_msg);
	if (error != 0)
		return (error);
	if (_Request_type == "POST")
	{
		del_method = full_msg.find("_method=DELETE");
		if (del_method != std::string::npos)
			_Request_type = "DELETE";
	}
	error = parse_request();
	if (error != 0)
		return (error);
	if (_Request_type == "POST")
		_Http_code = set_content_post(full_msg);
	
	if (_Http_code == 0)
		print_logs("Sender", _Request_type + " " + _Request_content, 1);
	
	return (_Http_code);
}