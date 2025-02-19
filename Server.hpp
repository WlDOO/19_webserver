/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najeuneh <najeuneh@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:32:12 by najeuneh          #+#    #+#             */
/*   Updated: 2025/02/19 17:58:52 by najeuneh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>	//getaddrinfo
#include <sys/socket.h>
#include <iostream>

#pragma once


uint32_t htonl(uint32_t hostlong);  //"Host to network long"
uint16_t htons(uint16_t hostshort); //"Host to network short"
uint32_t ntohl(uint32_t netlong);   //"Network to host long"
uint16_t ntohs(uint16_t netshort);  //"Network to host short"
//inet_pton << "pton” veut dire " presentation to network" ou, en français “présentation au réseau”


struct sockaddr_in
{
	sa_family_t		sin_family; //protocoles d adresse IP AF_INET
	in_port_t		sin_port;	//port a la quelle se co htons() pour indiquer le port
	struct in_addr	sin_addr;	//contient la représentation en entier d’une adresse IPv4
};

struct in_addr {
	uint32_t		s_addr;
};

struct addrinfo {
    int              ai_flags;
    int              ai_family;
    int              ai_socktype;
    int              ai_protocol;
    size_t           ai_addrlen;
    struct sockaddr *ai_addr;
    char            *ai_canonname;
    struct addrinfo *ai_next;
};

class Server
{
	private:
		
	public:
		Server();
		void	create_server(void);
		~Server();
};
