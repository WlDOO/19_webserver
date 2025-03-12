/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Read_send.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 13:35:52 by armitite          #+#    #+#             */
/*   Updated: 2025/03/12 00:12:27 by rafnasci         ###   ########.fr       */
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

	ifs.close();
    return oss.str();
}

std::string Server::html_response(int client_fd, std::string web_page) {

	std::ifstream ifs(web_page.c_str(), std::ios::binary);
	std::ostringstream oss_html;
	std::ostringstream oss;
    oss_html << ifs.rdbuf();
    std::string content = oss_html.str();
	std::string res;

	oss << "HTTP/1.1\r\n";
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
	std::cout << "verbs are : " << verbs << std::endl;
	found = verbs.find(" ", 0);
	_Request_type = verbs.substr(0, found);
	if (_Request_type == "POST")
		set_content_post(full_msg);
	verbs.erase(0, found);
	_Request_content = verbs.substr(2, (verbs.size() - 3));
	std::cout << "request type is : " << _Request_type << std::endl;
	std::cout << "request content is :" << _Request_content << std::endl;
	//return (verbs);
}

std::string	Server::html_request(int client_fd)
{
	if (_Request_type == "GET")
		return (request_get(client_fd));
	if (_Request_type == "POST")
		return (request_post(client_fd));

	return (request_get(client_fd));
}
void Server::send_data_to_socket(int i, struct epoll_event events[MAX_EVENTS]){

	int status;
	std::string msg_to_send;
	int sender_fd;
	
	sender_fd = (events)[i].data.fd;
	msg_to_send = html_request(sender_fd);
	std::cout << "----------------------------\n";
	std::cout <<"Request type :" << _Request_type << std::endl;
	std::cout <<"Request content :" << _Request_content << std::endl;
	std::cout << "MESSAGE TO SENDD :\n" << msg_to_send << std::endl;
	std::cout << "----------------------------\n";
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
			close(sender_fd);
			epoll_ctl(epoll_fd, EPOLL_CTL_DEL, sender_fd, NULL);
		}
	}
	else if (bytes_read == 0)  // Client has disconnected properly
	{
		std::cout << "request type :" << _Request_type << std::endl << "request content :" << _Request_content << std::endl;
		std::cout << "close fd :" << events[i].data.fd << std::endl;
		std::cout << "COOOUUUUUUUUUUUUTTTTTTTTTTTTTTTTTTTTTTTTTT\n";
		close(sender_fd);
		epoll_ctl(epoll_fd, EPOLL_CTL_DEL, sender_fd, NULL);
	}
    else
	{
		buffer[bytes_read] = '\0';
		std::string request(buffer);
		handleKeepAlive(request);
		set_request_type(buffer);
		send_data_to_socket(i, events);
    }
}