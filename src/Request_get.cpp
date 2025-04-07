/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request_get.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 20:10:46 by armitite          #+#    #+#             */
/*   Updated: 2025/04/07 22:12:54 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

std::string	Server::request_get(int client_fd) {

	std::string web_page;
	if (_Request_content == "favicon.ico")
		web_page = "favicon.png";
	else if (_Request_content.empty() || _Request_content == "/")
		web_page = "index.html";
	else
		web_page = _Request_content;
	std::ifstream ifs(web_page.c_str(), std::ios::binary);
	if (!ifs.is_open())
		return (html_error(404));

	return (html_response(client_fd, web_page));
}