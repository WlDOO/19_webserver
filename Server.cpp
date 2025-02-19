/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najeuneh <najeuneh@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:32:31 by najeuneh          #+#    #+#             */
/*   Updated: 2025/02/19 18:01:49 by najeuneh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <stdio.h>
#include <string.h>
#include <vector>

void Server::create_server(void)
{
	struct sockaddr_in	sa;
	int					socket_fd;
	int					client_fd;
	int					status;

	struct sockaddr_storage client_addr;
	socklen_t	addr_size;
}

int main(int ac, char **av)
{

}