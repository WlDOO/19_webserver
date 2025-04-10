/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse_request.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:35:41 by armitite          #+#    #+#             */
/*   Updated: 2025/04/10 15:59:34 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

int		Server::generate_autoindex(std::string loc) {

	DIR *dir = opendir(loc.c_str());
	if (!dir)
		return (1);
	std::string output;
	output += "<!DOCTYPE html>\r\n";
    output += "<html>\r\n<head>\r\n";
    output += "<title>Index of " + loc + "</title>\r\n";
    output += "<style>\r\n";
    output += "body { font-family: sans-serif; margin: 2em; }\r\n";
    output += "pre { background: #f8f8f8; padding: 1em; border-radius: 4px; }\r\n";
    output += "a { text-decoration: none; color: #0366d6; }\r\n";
    output += "a:hover { text-decoration: underline; }\r\n";
    output += "</style>\r\n</head>\r\n";
    output += "<body>\r\n";
    output += "<h1>Index of " + loc + "</h1>\r\n<hr>\r\n<pre>\r\n";
    output += "<a href=\"../\">../</a>\r\n";
	struct dirent *entry;
	while ((entry = readdir(dir)) != NULL) 
	{
    	if (!(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0))
		{
			std::string name = entry->d_name;
			output += "<a href=\"" + name + "\">" + entry->d_name + "</a>\r\n";
		}
	}
	closedir(dir);
	output += "</pre>\r\n<hr>\r\n</body>\r\n</html>\r\n";
	_Autoindex_output = output;
	std::cout << "html du autoindex : " << _Autoindex_output << std::endl;
	
	return (0);
}

int		Server::check_autoindex(int index_loc, std::string loc) {

	if (_Request_content == loc)
	{
		if (!(Conf.Server_par[0].Loc[index_loc].index.empty()))
		{
			_Request_content = Conf.Server_par[0].Loc[index_loc].index;
			std::cout << "Req content dans autoindex : " << _Request_content << std::endl;
			return (0);
		}
		if (Conf.Server_par[0].Loc[index_loc].autoindex == "on") {
	
			generate_autoindex(loc);
			_Is_autoindex = 1;
		}
		else
			return (403);
	}

	return (0);
}

int		Server::check_cgi(int index_loc) {

	std::size_t found;
	std::string ext;
	
	found = _Request_content.rfind(".");
	if (found == std::string::npos)
		return (1);
	ext = _Request_content.substr(found, _Request_content.size() - found);
	if (Conf.Server_par[0].Loc[index_loc].cgi_extonsions == ext) {

		_Script_path = Conf.Server_par[0].Loc[index_loc].cgi_pass;
		_Script = Conf.Server_par[0].root + _Request_content;
		//_Script = "Bad";
		_Is_cgi = 1;
		std::cout << "alors : " << _Is_cgi << " + " << _Script << " + " << _Script_path << std::endl;
		return (1);
	}
	
	return (0);
}

int		Server::check_vectors(std::vector<std::string> vector, std::string to_find) {
	
	size_t i;
	
	for (i = 0; i < vector.size(); i++) {

		if (to_find == vector[i])
		{
			std::cout << "ok" << std::endl;
			return (1);
		}
	}

	return (0);
}

std::string	Server::handle_alias(std::string alias, std::string loc) {

	std::string res;
	
	res = _Request_content;
	res.erase(0, loc.size());
	std::cout << "le content : " << _Request_content << std::endl;
	res = alias + res;
	std::cout << "le res : " << res << std::endl;

	return (res);

}

int		Server::allowed_method(int index_loc) {

	if (check_vectors(Conf.Server_par[0].Loc[index_loc].methods, _Request_type) == 1)
	{
		std::cout << "Good method" << std::endl;
		return (0);
	}
	std::cout << "Bad Method" << std::endl;
	return (1);
}

int		Server::parse_request(void) {

	size_t found;
	std::string loc;
	size_t i;
	int index_loc = -1;
	

	if (_Request_content == "asa.html" || _Request_content == "reve.html" || _Request_content.empty())
		return (0);
	if (_Request_content == "index.html" || _Request_content.empty())
	{	
		_Request_content = Conf.Server_par[0].index;
		_Request_type = "GET";
		return (0);
	}
	if (_Request_type == "DELETE")
		return (0);
	found = _Request_content.find("/");
	std::cout << _Request_content << std::endl;
	if (found == std::string::npos)
		return (404);
	loc = _Request_content.substr(0, found + 1);
	for (i = 0; i < Conf.Server_par[0].Loc.size(); i++) {

		if (loc == Conf.Server_par[0].Loc[i].Location)
		{
			index_loc = i;
			break ;
		}
	}
	if (index_loc == -1)
		return (404);
	if (allowed_method(index_loc) == 1)
		return (405);
	std::cout << "la loc :" << loc << std::endl;
	if (!Conf.Server_par[0].Loc[index_loc].alias.empty())
	{
		std::cout << Conf.Server_par[0].Loc[index_loc].alias << std::endl;
		_Request_content = handle_alias(Conf.Server_par[0].Loc[index_loc].alias, loc);
	}
	if (loc == "cgi-bin/") // || _Request_content.find("cgi-bin/") >= 0)
		check_cgi(index_loc);
	if (check_autoindex(index_loc, loc) != 0)
		return (403);
	// if (check_vectors(Conf.Server_par[0].Loc[index_loc].methods, _Request_type) != 1)
	// 	return (print_logs("Client", "Unothorized method", 2), 404);

	return (0);
}