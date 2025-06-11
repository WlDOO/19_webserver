/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 17:19:23 by rafnasci          #+#    #+#             */
/*   Updated: 2025/06/11 18:21:31 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

int Server::redirect(int index_loc)
{
	
	std::cout << "locdfsdfd : " << Conf.Server_par[0].Loc[index_loc].redirect_url << std::endl;
	// if (Conf.Server_par[0].Loc[index_loc].redirect_url)
	if (Conf.Server_par[0].Loc[index_loc].redirect_url == "/home/rafnasci/Projects/19_webserver/loin2/zebi")
	{
		_Request_content = "HTTP/1.1 301 Moved Permanently\r\n";
		_Request_content.append("Location: ");
		_Request_content.append(Conf.Server_par[0].Loc[index_loc].redirect_url);
		_Request_content.append("\r\n");
		_Request_content.append("Content-Length: 0\r\n");
		_Request_content.append("Connection: close\r\n");
		_Request_content.append("\r\n");
		return 1;
	}
	return 0;
}