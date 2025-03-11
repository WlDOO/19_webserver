/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request_get.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 20:10:46 by armitite          #+#    #+#             */
/*   Updated: 2025/03/11 13:17:23 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

std::string	Server::request_get(int client_fd) {

	std::string web_page;
	int i;
	std::string	pages[] = {
		"random_wikipedia.html",
		"page1.html",
		"page1_rep.html",
		"page2.html",
		"page3.html",
		"page4.html",
		"index.html",
		"res.html",
	};
	if (_Request_content.empty() || _Request_content == "/")
		web_page = "index.html";
	else
	{
		std::cout << "ici <" << std::endl;
		//web_page.assign(_Request_content, 1);
		for(i = 0; i < 9; i++) {
			if (_Request_content == pages[i])
			{
				web_page = pages[i];
				break ;
			}
		}
		if (i == 9)
			return (html_error_404(client_fd));
		//std::cout << "la page web : " << web_page << std::endl;
	}
	
	return (html_response(client_fd, web_page));
}