/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi_handle.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:47:34 by armitite          #+#    #+#             */
/*   Updated: 2025/06/17 15:36:01 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"
#include "../include/Cgi.hpp"

int	Cgi::cgi_handle(std::string const &Request_type, std::string const &Script, std::string const &Script_path, std::string &_Cgi_output) {

	std::stringstream ss;
	int fd[2];

    ss << "LAST_NAME=" << _Post_cgi_LN;
    std::string LAST_NAME = ss.str();
    ss.str("");

    ss << "FIRST_NAME=" << _Post_cgi_FN;
    std::string FIRST_NAME = ss.str();
	ss.str("");
	
	ss <<"REQUEST_METHOD=" << Request_type;
	std::string REQUEST_METHOD = ss.str();
	ss.str("");

	ss <<"CONTENT_LENGTH=" << _Post_cgi_content_lenght;
	std::string CONTENT_LENGTH = ss.str();
	ss.str("");

	ss <<"CONTENT_TYPE=" << _Post_cgi_content_type;
	std::string CONTENT_TYPE = ss.str();
	ss.str("");
	
	if (pipe(fd) == -1)
		return (500);
    pid_t pid = fork();
    
    std::cout << "Script path :" << Script << std::endl;
    char *envp[] = 
    {
            const_cast<char *>(LAST_NAME.c_str()),
            const_cast<char *>(FIRST_NAME.c_str()),
			const_cast<char *>(REQUEST_METHOD.c_str()),
			const_cast<char *>(CONTENT_LENGTH.c_str()),
			const_cast<char *>(CONTENT_TYPE.c_str()),
            NULL
    };

	if (pid < 0) 
		return (500);
	if (pid == 0) {
		
		dup2(fd[1], 1);
		close(fd[1]);
		close(fd[0]);
		std::vector<char *> argv;
		argv.push_back(const_cast<char *>(Script_path.c_str()));
		argv.push_back(const_cast<char *>(Script.c_str()));
        argv.push_back(NULL);
		if (execve(Script_path.c_str(), argv.data(), envp) == -1)
			_exit(1);
	}
	else
	{	
		close(fd[1]);
        int status;
        time_t start = time(NULL);
        int timeout_sec = 5;

        while (true) 
		{
            int waitpid_return = waitpid(pid, &status, WNOHANG);
            if (waitpid_return == pid) 
			{
                if (WIFEXITED(status) && WEXITSTATUS(status) != 0) 
				{
                    close(fd[0]);
                    return (500);
                }
                break;
            } 
			else if (waitpid_return == -1) 
			{
                close(fd[0]);
                return 500;
            }
            if (time(NULL) - start >= timeout_sec) 
			{
                kill(pid, SIGKILL);
                waitpid(pid, &status, 0);
                close(fd[0]);
                return (504);
            }
            usleep(100000);
        }

        std::string output;
        char buffer[BUFFER_SIZE];
        ssize_t bytes_read;

        while ((bytes_read = read(fd[0], buffer, sizeof(buffer))) > 0) 
		{
            output.append(buffer, bytes_read);
        }
        close(fd[0]);
        if (bytes_read == -1 || cgi_parse(output, _Cgi_output) == 1) 
		{
            return (500);
        }
    }


	return (0);
}