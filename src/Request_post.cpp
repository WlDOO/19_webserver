/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request_post.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 20:18:50 by armitite          #+#    #+#             */
/*   Updated: 2025/03/08 17:21:39 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

void		Server::set_content_post(std::string full_msg) {

	int found1;
	int found2;
	std::string content_type;
	std::string content_lenght;
	std::string boundary;
	std::string content;
	
	found1 = full_msg.find("boundary=", 0);
	full_msg.erase(0, found1);
	found1 = full_msg.find("\r\n", 0);
	boundary = full_msg.substr(10, found1 - 10);
	std::cout << "boundary : " << boundary << std::endl;
	found1 = full_msg.find("Content-Length:", 0);
	full_msg.erase(0, found1);
	found1 = full_msg.find("\r\n", 0);
	content_lenght = full_msg.substr(16, found1 - 16);
	full_msg.erase(0, found1);
	std::cout << "full_msg : " << full_msg << std::endl;
	found1 = full_msg.find(boundary + "\r\n", 0);
	found2 = full_msg.find(boundary + "--" + "\r\n", 0);
	content.assign(full_msg, found1, (found2 - found1));
	// _Post_file_name = content.substr(0, found1 - 1);
	found1 = content.find("Content-Type:", 0);
	content.erase(0, (found1 + 14));
	found1 = content.find("\r\n", 0);
	content_type = content.substr(0, found1);
	std::cout << "content_type : " << content_type << std::endl;
	found1 = content.find("\r\n\r\n", 0);
	content.erase(0, found1 + 4);
	_Post_content = content.substr(0, content.size());
	// found1 = content.find("\r\n", 0);
	// content.erase(0, found1 + 2);
	// found1 = content.find("---", 0);
	// _Post_content = content.substr(0, found1 - 3);
	request_post(6, "v1.txt");
	
	std::cout << "Le found 1 bis bis bis : " << found1 << std::endl;
	std::cout << "content_lenght : " << content_lenght << std::endl;
	std::cout << "_Post_content : " << _Post_content << std::endl;
	//std::cout << "content <><><><><><><><>: " << std::endl << content << std::endl;

	return ;
}

std::string	Server::request_post(int client_fd, std::string file_name) {

	std::string web_page = "page1_res.html";
	std::string dir = "../tmp/";
	std::string new_name = file_name;
	std::cout << new_name << std::endl;
	std::cout << _Post_content << std::endl;

	std::ofstream	ofs(new_name.c_str());
	ofs << _Post_content;
	ofs.close();
	
	return (html_response(client_fd, web_page));
}