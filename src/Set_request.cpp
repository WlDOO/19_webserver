/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Set_request.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raf <raf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:56:53 by armitite          #+#    #+#             */
/*   Updated: 2025/06/17 18:33:31 by raf              ###   ########.fr       */
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
	found = full_msg.find("localhost:", 0);
	_server_index = atoi(full_msg.substr(found + 10, full_msg.find("\n", found)).c_str());
	for (long unsigned int i = 0; i < Conf.Server_par.size(); i++){
		if (atoi(Conf.Server_par[i].listen[0].c_str()) == _server_index)
		{
			_server_index = i;
			break ;
		}
	}
	found = verbs.find(" ", 0);
	if (found == std::string::npos)
		return (print_logs("Client", "Incorrect content format", 2), 400);
	_Request_type = verbs.substr(0, found);
	if (_Request_type != "GET" && _Request_type != "POST" && _Request_type != "DELETE") 
		return (print_logs("Client", "Unsupported method: " + _Request_type, 2), 405);
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