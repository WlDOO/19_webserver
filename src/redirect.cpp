/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 17:19:23 by rafnasci          #+#    #+#             */
/*   Updated: 2025/06/12 15:56:21 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

int Server::redirect(int index_loc)
{
	
	std::cout << "locdfsdfd : " << Conf.Server_par[0].Loc[index_loc].redirect_url << std::endl;
	// if (Conf.Server_par[0].Loc[index_loc].redirect_url)
	std::cout << Conf.Server_par[0].Loc[index_loc].redirect_url << std::endl;
	if (Conf.Server_par[0].Loc[index_loc].redirect_url == "./loin/return.html")
	{
		std::cout << "Iciciciciciicicic" << std::endl;
		_Request_content = "HTTP/1.1 301 Moved Permanently\r\n";
		_Request_content.append("Location: https://www.google.com/\r\n");
		// _Request_content.append("google.com");
		_Request_content.append("\r\n");
		_Request_content.append("Content-Length: 0\r\n");
		_Request_content.append("Connection: keep-alive\r\n");
		_Request_content.append("\r\n");
		std::cout << _Request_content << std::endl;
		return 1;
	}
	return 0;
}