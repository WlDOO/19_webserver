/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi_handle.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:47:34 by armitite          #+#    #+#             */
/*   Updated: 2025/03/21 14:35:26 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

int	Server::cgi_handle(int client_fd) {

	if (client_fd == -1)
		return (1);
	 std::stringstream ss;
	 int fd[2];

    ss << "LAST_NAME=" << _Post_cgi_LN;
    std::string LAST_NAME = ss.str();
    ss.str("");

    ss << "FIRST_NAME=" << _Post_cgi_FN;
    std::string FIRST_NAME = ss.str();
	ss.str("");
	
	ss <<"REQUEST_METHOD=" << _Request_type;
	std::string REQUEST_METHOD = ss.str();
	ss.str("");

	ss <<"CONTENT_LENGTH=" << _Post_cgi_content_lenght;
	std::string CONTENT_LENGTH = ss.str();
	ss.str("");

	ss <<"CONTENT_TYPE=" << _Post_cgi_content_type;
	std::string CONTENT_TYPE = ss.str();
	ss.str("");
	
	if (pipe(fd) == -1)
		return (1);
    pid_t pid = fork();

    char *envp[] = 
    {
            const_cast<char *>(LAST_NAME.c_str()),
            const_cast<char *>(FIRST_NAME.c_str()),
			const_cast<char *>(REQUEST_METHOD.c_str()),
			const_cast<char *>(CONTENT_LENGTH.c_str()),
			const_cast<char *>(CONTENT_TYPE.c_str()),
            NULL
    };

	if (pid < 0) {
		
		std::cout << "Pid error cgi" << std::endl;
		return (1);
	}
	if (pid == 0) {
		
		dup2(fd[1], 1);
		close(fd[1]);
		close(fd[0]);
		std::string python_path = "/usr/bin/python3";
		std::vector<char *> argv;
		argv.push_back(const_cast<char *>(python_path.c_str()));
		argv.push_back(const_cast<char *>(_Script_path.c_str()));
        argv.push_back(NULL);
		execve(python_path.c_str(), argv.data(), envp);
		
		std::cout << "Execve failed" << std::endl;
		return (1);
	}
	else
	{	
		int bytes_read;
		std::string output;
		char buffer[BUFFER_SIZE] = {0};
		dup2(fd[0], 0);
		bytes_read = read(fd[0], buffer, BUFFER_SIZE - 1);
		if (bytes_read == -1)
		{
			close(fd[1]);
			close(fd[0]);
			std::cout << "Probleme read de cgi" << std::endl;
			return (1);
		}
		buffer[bytes_read] = '\0';
		close(fd[1]);
		close(fd[0]);
		std::ostringstream oss_tmp;
		oss_tmp << buffer;
		output = oss_tmp.str();
		std::cout << "Output du script : " << output << std::endl;

		cgi_parse(output);
	}

	waitpid(pid, NULL, 0);
	
	return (0);
}