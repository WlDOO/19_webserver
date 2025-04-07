/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request_post.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 20:18:50 by armitite          #+#    #+#             */
/*   Updated: 2025/03/19 14:40:51 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

int		Server::content_post_cgi(std::string full_msg) {

	size_t found1;
	std::string verbs;
	
	_Post_cgi_content_type = set_params_file(full_msg, "Content-Type: ", "\r\n");
	if (_Post_cgi_content_type.empty())
		return (print_logs("Client", "Cgi content type not found", 2), 1);
	_Post_cgi_content_lenght = set_params_file(full_msg, "Content-Length: ", "\r\n");
	if (_Post_cgi_content_lenght.empty())
		return (print_logs("Client", "Cgi content lenght not found", 2), 1);
	found1 = full_msg.find("\r\n\r\n", 0);
	full_msg.erase(0, found1);
	found1 = full_msg.find("nom=", 0);
	full_msg.erase(0, found1);
	found1 = full_msg.find("\r\n", 0);
	verbs = full_msg.substr(0, found1);
	_Post_cgi_LN = set_params_file(verbs, "nom=", "&");
	found1 = verbs.find("prenom=", 0);
	verbs.erase(0, found1);
	_Post_cgi_FN = set_params_file(verbs, "prenom=", "\0");

	cgi_handle(6);
	
	std::cout << "post cgi content : " << full_msg << std::endl;
	std::cout << "_Post_cgi_LN : " << _Post_cgi_LN << std::endl;
	std::cout << "_Post_cgi_FN : " << _Post_cgi_FN << std::endl;
	std::cout << "_Post_cgi_content_type : " << _Post_cgi_content_type << std::endl;
	std::cout << "_Post_cgi_content_lenght : " << _Post_cgi_content_lenght << std::endl;

	return (0);
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

int		Server::content_post_file(std::string full_msg) {

	size_t found1;
	size_t found2;
	std::string content_type;
	std::string content_lenght;
	std::string boundary;
	std::string content;
	
	boundary = set_params_file(full_msg, "boundary=", "\r\n");
	if (boundary.empty())
		return (print_logs("Client", "Boundary not found", 2), 1);
	content_lenght = set_params_file(full_msg, "Content-Length: ", "\r\n");
	if (content_lenght.empty())
		return (print_logs("Client", "Content lenght not found", 2), 1);
	found1 = full_msg.find(boundary + "\r\n", 0);
	if (found1 == std::string::npos)
		return (print_logs("Client", "Boundary problem (1)", 2), 1);
	full_msg.erase(0, found1 + boundary.size());
	found1 = full_msg.find(boundary + "\r\n", 0);
	if (found1 == std::string::npos)
		return (print_logs("Client", "Boundary problem (2)", 2), 1);
	found2 = full_msg.find(boundary + "--" + "\r\n", 0);
	if (found2 == std::string::npos)
		return (print_logs("Client", "Boundary problem (3, maybe curl)", 2), 1);
	content = full_msg.substr(found1, found2 + boundary.length() + 4);
	_Post_file_name = set_params_file(content, "filename=", "\r\n");
	if (_Post_file_name.empty())
		return (print_logs("Client", "File name not found", 2), 1);
	if (_Post_file_name.at(0) == '\"')
		_Post_file_name.erase(0, 1);
	if (_Post_file_name.at(_Post_file_name.size() - 1) == '\"')
		_Post_file_name.erase(_Post_file_name.size() - 1);
	content_type = set_params_file(content, "Content-Type: ", "\r\n");
	if (content_type.empty())
		return (print_logs("Client", "Content type not found", 2), 1);
	if (content_type != "text/plain")
		return (print_logs("Client", "Content type wrong format : " + content_type, 2), 1);
	std::cout << "content_type : " << content_type << std::endl;
	found1 = content.find("\r\n\r\n\r\n", 0);
	if (found1 != std::string::npos)
		return (print_logs("Client", "Empty file", 2), 1); // ici qd c'est empty file on peut return une error code diff 400 bad request
	found1 = content.find("\r\n\r\n", 0);
	if (found1 == std::string::npos)
		return (print_logs("Client", "Incorrect content format", 2), 1);
	content.erase(0, found1 + 4);
	found1 = content.find(boundary + "--" + "\r\n", 0);
	_Post_content = content.substr(0, found1 - 5);

	request_post(6);
	
	return (0);
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
		if (content_post_file(full_msg) != 0)
			return (1);
	}
	else if (_Is_cgi == 1)
	{
		if (content_post_cgi(full_msg) != 0)
			return (1);
	}
	else
		return (1);

	return (0);
}

std::string	Server::request_post(int client_fd) {

	std::string web_page = "page1_res.html";
	std::string dir = "/home/adduser/WEbserv/tmp/";
	std::string new_name = dir + _Post_file_name;
	std::cout << "ici" << std::endl;
	std::cout << new_name << std::endl;
	std::cout << _Post_content << std::endl;

	std::ofstream	ofs(new_name.c_str());
	ofs << _Post_content;
	ofs.close();
	
	return (html_response(client_fd, web_page));
}