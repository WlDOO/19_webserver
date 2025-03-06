/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request_post.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 20:18:50 by armitite          #+#    #+#             */
/*   Updated: 2025/03/06 17:30:24 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

void		Server::set_content_post(std::string full_msg) {

	int found1;
	int found2;
	std::string _Post_file_name;
	std::string content_type;
	std::string content;
	
	found1 = full_msg.find("Content-Disposition:", 0);
	found2 = full_msg.rfind("--", full_msg.size());
	std::cout << "Le found 1 : " << found1 << std::endl;
	std::cout << "Le found 2 : " << found2 << std::endl;
	std::cout << "La size : " << full_msg.size() << std::endl;
	content.assign(full_msg, found1, (found2 - found1));
	found1 = content.find("filename=", 0);
	content.erase(0, found1 + 10);
	found1 = content.find("\r\n", 0);
	_Post_file_name = content.substr(0, found1 - 1);
	found1 = content.find("Content-Type:", 0);
	content.erase(0, (found1 + 14));
	found1 = content.find("\r\n", 0);
	content_type = content.substr(0, found1);
	content.erase(0, content_type.size() + 2);
	found1 = content.find("\r\n", 0);
	content.erase(0, found1 + 2);
	found1 = content.find("---", 0);
	_Post_content = content.substr(0, found1 - 3);
	
	std::cout << "Le found 1 bis bis bis : " << found1 << std::endl;
	std::cout << "_Post_file_name : " << _Post_file_name << std::endl;
	std::cout << "content_type : " << content_type << std::endl;
	std::cout << "_Post_content : " << _Post_content << std::endl;
	std::cout << "content <><><><><><><><>: " << std::endl << content << std::endl;

	return ;
}

std::string	Server::request_post(int client_fd) {

	std::string web_page = "page1_res.html";
	std::string dir = "../tmp/";
	std::string new_name = dir + _Post_file_name;

	std::ofstream	ofs(new_name.c_str());
	ofs << _Post_content;
	ofs.close();
	
	return (html_response(client_fd, web_page));
}