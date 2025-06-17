/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raf <raf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 17:19:23 by rafnasci          #+#    #+#             */
/*   Updated: 2025/06/17 18:26:02 by raf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

int Server::redirect(int index_loc)
{
	if (!Conf.Server_par[_server_index].Loc[index_loc].redirect_url.empty())
	{
		_Request_content = "HTTP/1.1 301 Moved Permanently\r\n";
		_Request_content.append("Location: ");
		_Request_content.append(Conf.Server_par[_server_index].Loc[index_loc].redirect_url);
		_Request_content.append("\r\n");
		_Request_content.append("Content-Length: 0\r\n");
		_Request_content.append("Connection: keep-alive\r\n");
		_Request_content.append("\r\n");
		return 1;
	}
	return 0;
}