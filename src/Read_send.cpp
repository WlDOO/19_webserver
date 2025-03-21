/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Read_send.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:35:52 by armitite          #+#    #+#             */
/*   Updated: 2025/03/21 15:21:36 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

std::string Server::html_response_cgi(int client_fd) {

    std::string content = _Cgi_output;
	std::string res;
	std::ostringstream oss;

	oss << "HTTP/1.1 200 OK\r\n";
    oss << "Content-Type: text/html\r\n";
    oss << "Content-Length: " << content.size() << "\r\n";
	oss << "Connection: keep-alive\r\n";
    oss << "\r\n";
	oss << content << client_fd << std::endl;

	res = oss.str();

	return (res);
}

std::string Server::html_response(int client_fd, std::string web_page) {

	std::ifstream ifs(web_page.c_str(), std::ios::binary);
	std::ostringstream oss_html;
	std::ostringstream oss;
    oss_html << ifs.rdbuf();
    std::string content = oss_html.str();
	std::string res;

	oss << "HTTP/1.1 200 OK\r\n";
    if (web_page.find(".ico") != std::string::npos)
		oss << "Content-Type: image/x-icon\r\n";
	else
    	oss << "Content-Type: text/html\r\n";
    oss << "Content-Length: " << content.size() << "\r\n";
	oss << "Connection: keep-alive\r\n";
    oss << "\r\n";
	oss << content << client_fd << std::endl;

	ifs.close();
	res = oss.str();

	return (res);
}

std::string	Server::html_request(int client_fd)
{	
	if (_Error_flag == 1)
	{
		_Error_flag = 0;
		return (html_response(client_fd, "page1_rep_fail.html"));
	}
	if (_Request_type == "GET")
	{
		if (_Is_cgi == 1)
		{
			_Is_cgi = 0;
			std::cout << "Test find cgi" << std::endl;
			if (cgi_handle(client_fd) == 1)
				return (html_error_404(client_fd)); // Ici on doit envoyer error 400, bad request
			return (html_response_cgi(client_fd));
		}
		return (request_get(client_fd));
	}
	else if (_Request_type == "POST")
	{
		if (_Error_post == 1)
			return (html_response(client_fd, "page1_rep_fail.html"));
		else if (_Is_cgi == 1)
			return (html_response_cgi(client_fd));
		else
			return (html_response(client_fd, "page1_rep.html"));
	}
	// else if (_Request_type == "DELETE")
	// 	return (request_delete(client_fd));

	return (request_get(client_fd));
}
void Server::send_data_to_socket(int i, struct epoll_event events[MAX_EVENTS]){

	int status;
	std::string msg_to_send;
	int sender_fd;
	
	sender_fd = (events)[i].data.fd;
	msg_to_send = html_request(sender_fd);
	// std::cout << "----------------------------\n";
	// std::cout <<"Request type :" << _Request_type << std::endl;
	// std::cout <<"Request content :" << _Request_content << std::endl;
	// std::cout << "MESSAGE TO SENDD :\n" << msg_to_send << std::endl;
	// std::cout << "----------------------------\n";
	status = send(sender_fd, msg_to_send.c_str(), strlen(msg_to_send.c_str()), 0);
	if (status == -1) 
	{
		 if (errno == EAGAIN || errno == EWOULDBLOCK)
		{
			// Socket buffer is full, wait for EPOLLOUT to retry
			std::cout << "Socket buffer full, waiting for EPOLLOUT to retry send on fd: " << events[i].data.fd << std::endl;
			return;
		}
		 else
		{
			std::cerr << "[Server] Send error to client fd" << sender_fd << strerror(errno);
			close(sender_fd);
			epoll_ctl(epoll_fd, EPOLL_CTL_DEL, sender_fd, NULL);
		}
	}
	  // If all data was sent successfully, stop monitoring EPOLLOUT
    struct epoll_event event;
    event.events = EPOLLIN; // Only monitor for incoming data
    event.data.fd = events[i].data.fd;
    epoll_ctl(epoll_fd, EPOLL_CTL_MOD, events[i].data.fd, &event);
	if (!_Keep_alive)
	{
		std::cout << "COOOUUUUUUUUUUUUTTTTTTTTTTTTTTTTTTTTTTTTTT\n";
		close(sender_fd);
		epoll_ctl(epoll_fd, EPOLL_CTL_DEL, sender_fd, NULL);
	}
}

void Server::handleKeepAlive(const std::string &request)
{
	std::string request_lower;

	request_lower = request;
	std::transform(request_lower.begin(), request_lower.end(), request_lower.begin(), ::tolower);
	if (request_lower.find("connection: close") != std::string::npos)
		_Keep_alive = false;
	else
		_Keep_alive = true;
}

void Server::read_data_from_socket(int i, struct epoll_event events[MAX_EVENTS]) {

	char buffer[BUFFER_SIZE] = {0};
    std::string msg_to_send;
	std::ostringstream oss;
	std::ostringstream oss_tmp;
    int bytes_read;
	// int	found;
    //int status;
    int sender_fd;

	sender_fd = (events)[i].data.fd;
	bytes_read = read(sender_fd, buffer, BUFFER_SIZE - 1);
	if (bytes_read == -1)
	{
		if (errno == EAGAIN || errno == EWOULDBLOCK)  //  no data available yet or socket's buffer is full, try again later
			return ;
		else
		{
			perror("read failure");
			close(events[i].data.fd);
			epoll_ctl(epoll_fd, EPOLL_CTL_DEL, events[i].data.fd, NULL);
		}
	}
	else if (bytes_read == 0)  // Client has disconnected properly
	{
		std::cout << "close fd :" << events[i].data.fd << std::endl;
		close(events[i].data.fd);
		epoll_ctl(epoll_fd, EPOLL_CTL_DEL, events[i].data.fd, NULL);
	}
    else
	{	
		buffer[bytes_read] = '\0';
		std::string request(buffer);
		handleKeepAlive(request);
		if (set_request_type(buffer) == 1)
			_Error_flag = 1;
		send_data_to_socket(i, events);
    }
}