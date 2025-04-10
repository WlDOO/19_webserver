/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi_parse.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 14:01:47 by armitite          #+#    #+#             */
/*   Updated: 2025/04/10 16:06:59 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"
#include "../include/Cgi.hpp"

Cgi::Cgi() {

	return ;
}

Cgi::~Cgi() {

	return ;
}

void		Cgi::Set_fn(std::string fn) {

	_Post_cgi_FN = fn;
}
void		Cgi::Set_ln(std::string ln) {

	_Post_cgi_LN = ln;
}
void		Cgi::Set_content_type(std::string content_type) {

	_Post_cgi_content_type = content_type;
}
void		Cgi::Set_content_lenght(std::string content_lenght) {

	_Post_cgi_content_lenght = content_lenght;
}

int		Cgi::cgi_parse(std::string output, std::string &_Cgi_output) {

	size_t found;
	std::string Content_type;
	
	found = output.find("Content-Type:", 0);
	if (found == std::string::npos)
		return (1);
	output.erase(0, found + 8);
	found = output.find("\r\n");
	if (found == std::string::npos)
		return (1);
	Content_type = output.substr(0, found);
	if (found == std::string::npos)
		return (1);
	output.erase(0, found + 8);
	_Cgi_output = output;
	
	return (0);
}