/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   html_gen.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raf <raf@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 20:39:35 by rafnasci          #+#    #+#             */
/*   Updated: 2025/06/17 18:38:41 by raf              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

std::string Server::html_success(int code, const std::string& web_page) {
	
	std::ifstream ifs(web_page.c_str(), std::ios::binary);
	std::ostringstream oss_html;
	std::ostringstream oss;
    oss_html << ifs.rdbuf();
    std::string content = oss_html.str();
	std::string res;

	if (code == 200)
		oss << "HTTP/1.1 "<< code <<" OK\r\n";
	if (code == 201)
		oss << "HTTP/1.1 "<< code <<" Created\r\n";
    oss << "Content-Type: text/html\r\n";
    oss << "Content-Length: " << content.size() << "\r\n";
	oss << "Connection: keep-alive\r\n";
    oss << "\r\n";
	oss << content;

	return (oss.str());
}

std::string Server::html_error(int code) {
	
	std::string content;
	std::ostringstream oss;

	content = check_error_dir(code);
	oss << "HTTP/1.1 "<< code <<" OK\r\n";
    oss << "Content-Type: text/html\r\n";
    oss << "Content-Length: " << content.size() << "\r\n";
	oss << "Connection: keep-alive\r\n";
    oss << "\r\n";
	oss << content;

	return (oss.str());
}

std::string	Server::check_error_dir(int code) {
	size_t				i;
	std::ostringstream	oss;
	std::ostringstream	tmp;
	
	tmp << code;
	i = -1;
	while (++i < Conf.Server_par[_server_index].error_page_num.size() - 1) {
		if (Conf.Server_par[_server_index].error_page_num[i] == tmp.str())
			break;
	}
	if ((Conf.Server_par[_server_index].error_page_num[i] == tmp.str())) {
		std::ifstream ifs(Conf.Server_par[_server_index].error_page_loc[i].c_str(), std::ios::binary);
		oss << ifs.rdbuf();
		return (oss.str());
	}
	else
		return (html_error_gen(code, get_msg(code)));
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
		case 411 :
			return ("Length Required");
		case 413 :
			return ("Request Too Large");
		case 415 :
			return ("Unsupported Media Type");
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