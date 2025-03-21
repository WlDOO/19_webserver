/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Set_request.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:56:53 by armitite          #+#    #+#             */
/*   Updated: 2025/03/21 15:39:47 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

int	Server::request_custom_type(std::string full_msg) {

	size_t	found;

	found = full_msg.find("GET", 0);
	if (found == std::string::npos)
	{
		found = full_msg.find("POST", 0);
		if (found == std::string::npos)
			return (print_logs("Sender", " no request type", 2), 1);
		else
			_Request_type = "POST";
	}
	else
		_Request_type = "GET";
	
	return (0);
}

int	Server::request_custom_content(std::string full_msg) {

	size_t	found;
	size_t i = 0;

	found = full_msg.find(_Request_type, 0);
	full_msg.erase(0, found + _Request_type.length());
	if (full_msg.empty())
		return (print_logs("Sender", _Request_type + " full_msg empty", 2), 1);
	while (i < full_msg.length())
	{
		if (full_msg.at(i) == ' ')
			i++;
		else
			break ;
	}
	full_msg.erase(0, i);
	if (full_msg.at(0) == '/')
		full_msg.erase(0, 1);
	found = full_msg.find("\n", 0);
	_Request_content = full_msg.substr(0, found);
	if (_Request_content.empty())
		return (print_logs("Sender", _Request_type + " Request type empty", 2), 1);
	
	return (0);
}

int	Server::set_request_custom(std::string full_msg) {

	std::string verbs;
	
	if (request_custom_type(full_msg) == 1)
		return (1);
	if (request_custom_content(full_msg) == 1)
		return (1);
	
	return (0);
}

int	Server::set_request_http(std::string full_msg) {

	std::string verbs;
	size_t	found;
	
	found = full_msg.find("HTTP/1.1", 0);
	verbs = full_msg.substr(0, found);
	found = verbs.find(" ", 0);
	_Request_type = verbs.substr(0, found);
	verbs.erase(0, found);
	_Request_content = verbs.substr(2, (verbs.size() - 3));
	
	return (0);
}

int	Server::set_request_type(char buffer[BUFSIZ]) {

	std::ostringstream oss_tmp;
	std::string sender_msg;
	std::string full_msg;
	std::string verbs;
	size_t	found;

	oss_tmp << buffer;
	sender_msg = oss_tmp.str();
	full_msg.assign(sender_msg);
	if (full_msg.find("favicon.ico") != std::string::npos)
		return (0);
	std::cout << " full_msg is : " << full_msg << std::endl;
	found = full_msg.find("HTTP/1.1", 0);
	if (found != std::string::npos)
	{
		if (set_request_http(full_msg) == 1)
			return (1);
	}
	else
	{
		if (set_request_custom(full_msg) == 1)
			return (1);
	}
	if (parse_request() == 1)
		return (1);
	if (_Request_type == "POST")
	{
		if (set_content_post(full_msg) == 1)
			return (1);
	}
	
	print_logs("Sender", _Request_type + " " + _Request_content, 1);
	
	return (0);
}