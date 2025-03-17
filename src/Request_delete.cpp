/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request_delete.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:58:09 by rafnasci          #+#    #+#             */
/*   Updated: 2025/03/17 17:18:19 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

std::string Server::request_delete(int client_fd)
{
	std::string file_path;
	std::string send;
	
	if (_Request_content.find("html/") != std::string::npos)
		file_path = "html/" + _Request_content;  // changer "html/" par le nom du repertoire ou seront les trucs a delete
	else
		file_path = _Request_content;
	
	if (access(file_path.c_str(), F_OK) == 0)
	{
		print_logs("Client", "File Deleted", 1);
		if (std::remove(file_path.c_str()) == 0)
		{
			send = "HTTP/1.1 204 No Content\r\n";
			send += "Connection : keep-alive\r\n";
			send += "\r\n";
			return (send);
		}
		else
			return (html_error_500(client_fd));
	}
	else
		return (html_error_404(client_fd));
}