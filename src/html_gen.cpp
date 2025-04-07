/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   html_gen.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 20:39:35 by rafnasci          #+#    #+#             */
/*   Updated: 2025/04/07 21:58:51 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

std::string Server::html_success(int code, const std::string& web_page) {
	
	std::ostringstream oss;

	if (code == 200)
		oss << "HTTP/1.1 "<< code <<" OK\r\n";
	else
	oss << "HTTP/1.1 "<< code <<" Created\r\n";
    oss << "Content-Type: text/html\r\n";
    oss << "Content-Length: " << web_page.size() << "\r\n";
	oss << "Connection: keep-alive\r\n";
    oss << "\r\n";
	oss << web_page;

	return (oss.str());
}

std::string Server::html_error(int code) {

    std::string content = html_error_gen(code, get_msg(code));
	std::ostringstream oss;

	oss << "HTTP/1.1 "<< code <<" OK\r\n";
    oss << "Content-Type: text/html\r\n";
    oss << "Content-Length: " << content.size() << "\r\n";
	oss << "Connection: keep-alive\r\n";
    oss << "\r\n";
	oss << content;

	return (oss.str());
}

std::string	Server::get_msg(int code) {
	
	switch (code) {
		case 400 :
			return ("Bad Request");
		case 403 :
			return ("Forbidden");
		case 404 :
			return ("Not Found");
		case 405 :
			return ("Method Not Allowed");
		case 413 :
			return ("Request Too Large");
		case 500 :
			return ("Internal Server Error");
		case 504 :
			return ("Gateway Timeout");
		default:
			return ("Unknown Request");		
	}
}

std::string	Server::html_error_gen(int error_code, const std::string& msg) {
	
	std::ostringstream content;

	content << "<!DOCTYPE html>\n"
			<< "<html lang=\"fr\">\n"
			<< "<head>\n"
			<<"    <meta charset=\"UTF-8\">\n"
			<<"    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
			<<"    <title>Erreur " << error_code << "</title>\n"
			<<"    <style>\n"
			<<"        body {\n"
			<<"            font-family: Arial, sans-serif;\n"
			<<"            background-color: #f4f4f9;\n"
			<<"            color: #333;\n"
			<<"            text-align: center;\n"
			<<"            padding: 50px;\n"
			<<"        }\n"
			<<"        h1 {\n"
			<<"            font-size: 100px;\n"
			<<"            color: #e74c3c;\n"
			<<"        }\n"
			<<"        p {\n"
			<<"            font-size: 20px;\n"
			<<"            margin-top: 20px;\n"
			<<"        }\n"
			<<"        a {\n"
			<<"            text-decoration: none;\n"
			<<"            color: #3498db;\n"
			<<"            font-weight: bold;\n"
			<<"        }\n"
			<<"        a:hover {\n"
			<<"            text-decoration: underline;\n"
			<<"        }\n"
			<<"    </style>\n"
			<<"</head>\n"
			<<"<body>\n"
			<<"    <h1>Erreur " <<error_code <<"</h1>\n"
			<<"    <p>" << msg << "</p>\n"
			<<"    <p><a href=\"/\">Retour à l'accueil</a></p>\n"
			<<"</body>\n"
			<<"</html>\n";

	return (content.str());
}