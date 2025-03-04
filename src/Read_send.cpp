/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Read_send.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:35:52 by armitite          #+#    #+#             */
/*   Updated: 2025/03/04 17:20:27 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

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

    return oss.str();
}

void	Server::set_request_type(char buffer[BUFSIZ]) {

	std::ostringstream oss_tmp;
	std::string sender_msg;
	std::string full_msg;
	std::string verbs;
	int	found;

	oss_tmp << buffer;
	sender_msg = oss_tmp.str();
	full_msg.assign(sender_msg);
	std::cout << " full_msg is : " << full_msg << std::endl;
	found = full_msg.find("HTTP/1.1", 0);
	verbs = full_msg.substr(0, found);
	std::cout << "le found : " << found << std::endl;
	std::cout << " verbs are : " << verbs << std::endl;
	found = verbs.find(" ", 0);
	_Request_type = verbs.substr(0, found);
	verbs.erase(0, found);
	_Request_content = verbs.substr(2, (verbs.size() - 3));
	std::cout << " request type is : " << _Request_type << std::endl;
	std::cout << " request content is :" << _Request_content << std::endl;
	//return (verbs);
}

std::string	Server::html_request(int client_fd)
{
	std::string web_page;
	int i;
	std::string	pages[] = {
		"page1.html",
		"page2.html",
		"page3.html",
		"index.html",
		"res.html",
	};
	if (_Request_content.empty())
		web_page = "index.html";
	else
	{
		std::cout << "ici <" << std::endl;
		//web_page.assign(_Request_content, 1);
		for(i = 0; i < 6; i++) {
			if (_Request_content == pages[i])
			{
				web_page = pages[i];
				break ;
			}
		}
		if (i == 6)
			return (html_error_404(client_fd));
		//std::cout << "la page web : " << web_page << std::endl;
	}
	std::ifstream ifs(web_page.c_str(), std::ios::binary);
	std::ostringstream oss_html;
	std::ostringstream oss;
    oss_html << ifs.rdbuf();
    std::string content = oss_html.str();
	std::string res;

	oss << "HTTP/1.1 200 OK\r\n";
    oss << "Content-Type: text/html\r\n";
    oss << "Content-Length: " << content.size() << "\r\n";
	oss << "Connection: keep-alive\r\n";
    oss << "\r\n";
	oss << content << client_fd << std::endl;
	res = oss.str();
	
	// _Request_content.clear();
	ifs.close();
	return (res);
}
void Server::send_data_to_socket(int i, std::vector<struct pollfd>& poll_fds){

	int status;
	std::string msg_to_send;
	int sender_fd;
	
	sender_fd = (poll_fds)[i].fd;
	msg_to_send = html_request(sender_fd);
	status = send(sender_fd, msg_to_send.c_str(), strlen(msg_to_send.c_str()), 0);
	if (status == -1) 
	{
		std::cerr << "[Server] Send error to client fd" << sender_fd << strerror(errno);
	}
}

void Server::read_data_from_socket(int i, std::vector<struct pollfd> &poll_fds, int *poll_count, int server_socket) {

	char buffer[BUFSIZ];
    std::string msg_to_send;
	std::ostringstream oss;
	std::ostringstream oss_tmp;
    int bytes_read;
	// int	found;
    //int status;
    int sender_fd;
	(void)server_socket;

	sender_fd = (poll_fds)[i].fd;
	memset(&buffer, '\0', sizeof buffer);
	bytes_read = recv(sender_fd, buffer, BUFSIZ, 0);
	if (bytes_read <= 0) {
		if (bytes_read == 0) {
			std::cout << sender_fd << " Client socket closed connection." << std::endl;
		}
		else {
			std::cerr << "[Server] Recv error: " << strerror(errno);
		}
		close(sender_fd); // Ferme la socket
		del_from_poll_fds(poll_fds, i, poll_count);
    }
    else {
		set_request_type(buffer);
		// if (_Request_content == "favicon.ico")
		// {
		// 	std::cout << "Flavico !" << std::endl;
		// 	return ;
		// }
		send_data_to_socket(i, poll_fds);
    }
}