/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Errors.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:11:35 by rafnasci          #+#    #+#             */
/*   Updated: 2025/03/17 17:32:41 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

std::string Server::html_error_400(int client_fd) {

	std::ifstream ifs("400.html", std::ios::binary);
	std::ostringstream oss_html;
	std::ostringstream oss;
    oss_html << ifs.rdbuf();
    std::string content = oss_html.str();
	std::string res;

    oss << "HTTP/1.1 400 Bad Request\r\n";
    oss << "Content-Type: text/html\r\n";
    oss << "Content-Length: " << content.size() << "\r\n";
    oss << "Connection: keep-alive\r\n";
    oss << "\r\n";
    oss << content << client_fd << std::endl;

	ifs.close();
    return oss.str();
}

std::string Server::html_error_403(int client_fd) {

	std::ifstream ifs("403.html", std::ios::binary);
	std::ostringstream oss_html;
	std::ostringstream oss;
    oss_html << ifs.rdbuf();
    std::string content = oss_html.str();
	std::string res;

    oss << "HTTP/1.1 403 Forbidden\r\n";
    oss << "Content-Type: text/html\r\n";
    oss << "Content-Length: " << content.size() << "\r\n";
    oss << "Connection: keep-alive\r\n";
    oss << "\r\n";
    oss << content << client_fd << std::endl;

	ifs.close();
    return oss.str();
}

std::string Server::html_error_404(int client_fd) {

	std::ifstream ifs("404.html", std::ios::binary);
	std::ostringstream oss_html;
	std::ostringstream oss;
    oss_html << ifs.rdbuf();
    std::string content = oss_html.str();
	std::string res;

    oss << "HTTP/1.1 404 Not Found\r\n";
    oss << "Content-Type: text/html\r\n";
    oss << "Content-Length: " << content.size() << "\r\n";
    oss << "Connection: keep-alive\r\n";
    oss << "\r\n";
    oss << content << client_fd << std::endl;

	ifs.close();
    return oss.str();
}

std::string Server::html_error_405(int client_fd) {

	std::ifstream ifs("405.html", std::ios::binary);
	std::ostringstream oss_html;
	std::ostringstream oss;
    oss_html << ifs.rdbuf();
    std::string content = oss_html.str();
	std::string res;

    oss << "HTTP/1.1 405 Method Not allowed\r\n";
    oss << "Content-Type: text/html\r\n";
    oss << "Content-Length: " << content.size() << "\r\n";
    oss << "Connection: keep-alive\r\n";
    oss << "\r\n";
    oss << content << client_fd << std::endl;

	ifs.close();
    return oss.str();
}

std::string Server::html_error_408(int client_fd) {

	std::ifstream ifs("408.html", std::ios::binary);
	std::ostringstream oss_html;
	std::ostringstream oss;
    oss_html << ifs.rdbuf();
    std::string content = oss_html.str();
	std::string res;

    oss << "HTTP/1.1 408 Request Timeout\r\n";
    oss << "Content-Type: text/html\r\n";
    oss << "Content-Length: " << content.size() << "\r\n";
    oss << "Connection: keep-alive\r\n";
    oss << "\r\n";
    oss << content << client_fd << std::endl;

	ifs.close();
    return oss.str();
}

std::string Server::html_error_413(int client_fd) {

	std::ifstream ifs("413.html", std::ios::binary);
	std::ostringstream oss_html;
	std::ostringstream oss;
    oss_html << ifs.rdbuf();
    std::string content = oss_html.str();
	std::string res;

    oss << "HTTP/1.1 413 Payload too large\r\n";
    oss << "Content-Type: text/html\r\n";
    oss << "Content-Length: " << content.size() << "\r\n";
    oss << "Connection: keep-alive\r\n";
    oss << "\r\n";
    oss << content << client_fd << std::endl;

	ifs.close();
    return oss.str();
}

std::string Server::html_error_500(int client_fd) {

	std::ifstream ifs("500.html", std::ios::binary);
	std::ostringstream oss_html;
	std::ostringstream oss;
    oss_html << ifs.rdbuf();
    std::string content = oss_html.str();
	std::string res;

    oss << "HTTP/1.1 500 Internal Serveer Error\r\n";
    oss << "Content-Type: text/html\r\n";
    oss << "Content-Length: " << content.size() << "\r\n";
    oss << "Connection: keep-alive\r\n";
    oss << "\r\n";
    oss << content << client_fd << std::endl;

	ifs.close();
    return oss.str();
}