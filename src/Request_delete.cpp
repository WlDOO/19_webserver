/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request_delete.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:58:09 by rafnasci          #+#    #+#             */
/*   Updated: 2025/04/02 19:08:16 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

std::string Server::request_delete(int client_fd)
{
	std::string file_path;
	std::string send;
	
	if (_Request_content.find("html/") == std::string::npos)
		file_path = "html/" + _Request_content;  // changer "html/" par le nom du repertoire ou seront les trucs a delete
	else
		file_path = _Request_content;
	
	if (access(file_path.c_str(), F_OK) == 0)
	{
		if (std::remove(file_path.c_str()) == 0)
		{
			return (html_response(client_fd, "conf_del.html"));
		}
		else
		{
			print_logs("Client", "Delete failed: " + std::string(strerror(errno)), 2);
			return (html_error_500(client_fd));
		}
	}
	else
	{
		print_logs("Client", "Delete failed: " + std::string(strerror(errno)), 2);
		return (html_error_404(client_fd));
	}
}

int		Server::content_del(std::string full_msg) {

	size_t found1;
	std::string verbs;
	std::string content;
	
	_Request_type = "DELETE";
	content = set_params_file(full_msg, "Content-Length: ", "\r\n");
	if (content.empty())
		return (print_logs("Client", "Cgi content lenght not found", 2), 1);
	content = set_params_file(full_msg, "Content-Type: ", "\r\n");
	if (content.empty())
		return (print_logs("Client", "Cgi content type not found", 2), 1);
	found1 = full_msg.find("\r\n\r\n", 0);
	full_msg.erase(0, found1);
	_Request_content = set_params_file(full_msg, "filename=", "\0");
	
	return (0);
}