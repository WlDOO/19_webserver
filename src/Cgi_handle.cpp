/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:47:34 by armitite          #+#    #+#             */
/*   Updated: 2025/03/10 17:28:18 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

void	Server::cgi_handle(int client_fd) {

	if (client_fd == -1)
		return ;
	pid_t pid = fork();

	if (pid < 0) {
		
		std::cout << "Pid error cgi" << std::endl;
		_exit(1);
	}
	if (pid == 0) {
	
		std::string python_path = "/usr/bin/python3";
		std::vector<char *> argv;
		argv.push_back(const_cast<char *>(python_path.c_str()));
		argv.push_back(const_cast<char *>("/home/armitite/Cursus/19_webserver/random_wikipedia.py"));
        argv.push_back(NULL);
		execve(python_path.c_str(), argv.data(), NULL);
		
		std::cout << "Execve failed" << std::endl;
		_exit(1);
	}

	waitpid(pid, NULL, 0);
}