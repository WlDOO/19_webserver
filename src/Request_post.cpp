/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request_post.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raf <raf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 20:18:50 by armitite          #+#    #+#             */
/*   Updated: 2025/06/17 18:31:50 by raf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"
#include "../include/Cgi.hpp"

int		Server::content_post_cgi(std::string full_msg) {

	size_t found1;
	std::string verbs;
	std::string content_type;
	std::string content_lenght;
	std::string last_name;
	std::string first_name;
	
	content_type = set_params_file(full_msg, "Content-Type: ", "\r\n");
	if (content_type.empty())
		return (print_logs("Client", "Cgi content type not found", 2), 400);
	content_lenght = set_params_file(full_msg, "Content-Length: ", "\r\n");
	if (content_lenght.empty())
		return (print_logs("Client", "Cgi content lenght not found", 2), 411);
	found1 = full_msg.find("\r\n\r\n", 0);
	if (found1 == std::string::npos)
		return (print_logs("Client", "Bad request (1)", 2), 400);
	full_msg.erase(0, found1);
	found1 = full_msg.find("nom=", 0);
	if (found1 == std::string::npos)
		return (print_logs("Client", "Bad data, missing 'nom'", 2), 400);
	full_msg.erase(0, found1);
	found1 = atoi(content_lenght.c_str());
	if (found1 == 0)
		return (print_logs("Client", "Bad request (2)", 2), 400);
	verbs = full_msg.substr(0, found1);
	last_name = set_params_file(verbs, "nom=", "&");
	if (last_name.empty())
		return (print_logs("Client", "Cgi last name not found", 2), 400);
	found1 = verbs.find("prenom=", 0);
	if (found1 == std::string::npos)
		return (print_logs("Client", "Bad request (3)", 2), 400);
	verbs.erase(0, found1);
	first_name = set_params_file(verbs, "prenom=", "\0");
	if (last_name.empty())
		return (print_logs("Client", "Cgi first name not found", 2), 400);
	
	cgi->Set_fn(first_name);
	cgi->Set_ln(last_name);
	cgi->Set_content_lenght(content_lenght);
	cgi->Set_content_type(content_type);

	return (201);
}

std::string		Server::set_params_file(std::string full_msg, std::string to_find, std::string to_find2) {

	size_t found;
	std::string result;
	
	found = full_msg.find(to_find, 0);
	if (found == std::string::npos)
		return (result);
	full_msg.erase(0, found);
	found = full_msg.find(to_find2, 0);
	if (found == std::string::npos)
		return (result);
	result = full_msg.substr(to_find.size(), found - to_find.size());

	return (result);
}

int check_digit_content_lenght(std::string nbr) {

	size_t i;

	i = 0;
	while (i < nbr.size()) {
		if (!isdigit(nbr.at(i)))
			return (1);
		i++;
	}

	return (0);
}

int		Server::content_post_file(std::string full_msg) {

	size_t found1;
	size_t found2;
	std::string content_type;
	std::string content_lenght;
	std::string boundary;
	std::string content;
	
	boundary = set_params_file(full_msg, "boundary=", "\r\n");
	if (boundary.empty())
		return (print_logs("Client", "Boundary not found", 2), 400);
	content_lenght = set_params_file(full_msg, "Content-Length: ", "\r\n");
	if (content_lenght.empty())
		return (print_logs("Client", "Content lenght not found", 2), 411);
	if (check_digit_content_lenght(content_lenght) == 0) {
		int size = std::atoi(content_lenght.c_str());
		if (size >= std::atoi(Conf.Server_par[_server_index].client_max_body_size.c_str()))
			return (print_logs("Client", "Body size too large", 2), 413);
	}
	else
		return (print_logs("Client", "Body size too large", 2), 400);
	found1 = full_msg.find(boundary + "\r\n", 0);
	if (found1 == std::string::npos)
		return (print_logs("Client", "Boundary problem (1)", 2), 400);
	full_msg.erase(0, found1 + boundary.size());
	found1 = full_msg.find(boundary + "\r\n", 0);
	if (found1 == std::string::npos)
		return (print_logs("Client", "Boundary problem (2)", 2), 400);
	found2 = full_msg.find(boundary + "--" + "\r\n", 0);
	if (found2 == std::string::npos)
		return (print_logs("Client", "Boundary problem (3, maybe curl)", 2), 400);
	content = full_msg.substr(found1, found2 + boundary.length() + 4);
	_Post_file_name = set_params_file(content, "filename=", "\r\n");
	if (_Post_file_name.empty())
		return (print_logs("Client", "File name not found", 2), 400);
	if (_Post_file_name.at(0) == '\"')
		_Post_file_name.erase(0, 1);
	if (_Post_file_name.at(_Post_file_name.size() - 1) == '\"')
		_Post_file_name.erase(_Post_file_name.size() - 1);
	content_type = set_params_file(content, "Content-Type: ", "\r\n");
	if (content_type.empty())
		return (print_logs("Client", "Content type not found", 2), 400);
	if (content_type != "text/plain")
		return (print_logs("Client", "Content type wrong format : " + content_type, 2), 415);
	found1 = content.find("\r\n\r\n\r\n", 0);
	if (found1 != std::string::npos)
		return (print_logs("Client", "Empty file", 2), 400); // ici qd c'est empty file on peut return une error code diff 400 bad request
	found1 = content.find("\r\n\r\n", 0);
	if (found1 == std::string::npos)
		return (print_logs("Client", "Incorrect content format", 2), 400);
	content.erase(0, found1 + 4);
	found1 = content.find(boundary + "--" + "\r\n", 0);
	_Post_content = content.substr(0, found1 - 5);

	return (request_post());
}

int		Server::set_content_post(std::string full_msg) {

	int found1;
	std::string content_type;
	std::string content_lenght;
	std::string boundary;
	std::string content;
	
	found1 = full_msg.find("boundary=", 0);
	if (found1 >= 0)
	{
		return (content_post_file(full_msg));
	}
	else if (_Is_cgi == 1)
	{
		return (content_post_cgi(full_msg));
	}

	return (400);
}

int	Server::request_post(void) {

	std::string dir = Conf.Server_par[_server_index].root + "tmp/";
	std::string new_name = dir + _Post_file_name;

	std::ofstream	ofs(new_name.c_str());
	if (!ofs.is_open())
		return (500);
	ofs << _Post_content;
	ofs.close();
	
	return (201);
}