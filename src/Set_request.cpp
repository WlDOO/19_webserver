/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Set_request.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:56:53 by armitite          #+#    #+#             */
/*   Updated: 2025/04/02 19:13:27 by rafnasci         ###   ########.fr       */
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
		{
			found = full_msg.find("DELETE", 0);
			if (found == std::string::npos)
				return (print_logs("Sender", " no request type", 2), 1);
			else
				_Request_type = "DELETE";
		}
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

void	Server::set_request_custom(std::string full_msg) {

	std::string verbs;
	
	if (request_custom_type(full_msg) == 1)
		return ;
	if (request_custom_content(full_msg) == 1)
		return ;
	if (_Request_type == "POST")
		set_content_post(_Request_content);
	
	print_logs("Sender", _Request_type + " " + _Request_content, 1);
}

void	Server::set_request_http(std::string full_msg) {

	std::string verbs;
	size_t	found;
	size_t del_method;
	
	found = full_msg.find("HTTP/1.1", 0);
	verbs = full_msg.substr(0, found);
	found = verbs.find(" ", 0);
	_Request_type = verbs.substr(0, found);
	std::cout << "Request type: " << _Request_type << std::endl;
	if (_Request_type == "POST")
	{
		del_method = full_msg.find("_method=DELETE");
		if (del_method != std::string::npos)
			_Error_post = content_del(full_msg);
		else
			_Error_post = set_content_post(full_msg);
	}
	if (_Request_type == "GET")
	{
		verbs.erase(0, found);
		_Request_content = verbs.substr(2, (verbs.size() - 3));
	}
	std::cout << "THE _REQUEST: " << _Request_content << std::endl;
	print_logs("Sender", _Request_type + " " + _Request_content, 1);
}

void	Server::set_request_type(char buffer[BUFSIZ]) {

	std::ostringstream oss_tmp;
	std::string sender_msg;
	std::string full_msg;
	std::string verbs;
	size_t	found;

	oss_tmp << buffer;
	sender_msg = oss_tmp.str();
	full_msg.assign(sender_msg);
	if (full_msg.find("favicon.ico") != std::string::npos)
		return ;
	std::cout << " full_msg is : " << full_msg << std::endl;
	found = full_msg.find("HTTP/1.1", 0);
	if (found != std::string::npos)
		set_request_http(full_msg);
	else
		set_request_custom(full_msg);
	return ;
}