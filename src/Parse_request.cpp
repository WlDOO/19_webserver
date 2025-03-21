/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse_request.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:35:41 by armitite          #+#    #+#             */
/*   Updated: 2025/03/21 16:27:38 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

int		Server::check_cgi(void) {

	std::size_t found;
	std::string ext;
	std::string ext_tmp;
	
	ext_tmp = ".py";
	found = _Request_content.rfind(".");
	ext = _Request_content.substr(found, _Request_content.size() - found);
	std::cout << "ext_tmp : " << ext_tmp << std::endl;
	std::cout << "ext : " << ext << std::endl;
	if (ext == ext_tmp)
	{
		_Script_path = _Request_content;
		_Is_cgi = 1;
		std::cout << "alors :" << _Is_cgi << " + " << _Script_path << std::endl;
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

int		Server::parse_request(void) {

	size_t found;
	std::string loc;
	std::vector<std::string> myloc;
	std::vector<std::string> methods;
	size_t i;
	int index_loc = -1;
	
	if (_Request_content == "index.html" || _Request_content.empty())
	{	
		_Request_content = Conf.Server_par[0].index;
		return (0);
	}
	found = _Request_content.find("/");
	if (found == std::string::npos)
		return (1);
	loc = _Request_content.substr(0, found + 1);
	for (i = 0; i < Conf.Server_par[0].Loc.size(); i++) {

		if (loc == Conf.Server_par[0].Loc[i].Location)
		{
			std::cout << "ok" << std::endl;
			index_loc = i;
		}
		std::cout << "les loc : " << Conf.Server_par[0].Loc[i].Location << std::endl;
	}
	if (index_loc == -1)
		return (1);
	// if (!Conf.Server_par[0].Loc[index_loc].redirect_url.empty())
	// 	std::cout << Conf.Server_par[0].Loc[index_loc].redirect_url.empty() << std::endl;
	//std::cout << "la methode :" << Conf.Server_par[0].Loc[index_loc].methods[0] << std::endl;
	std::cout << "la loc :" << loc << std::endl;
	if (!Conf.Server_par[0].Loc[index_loc].alias.empty())
	{
		std::cout << Conf.Server_par[0].Loc[index_loc].alias << std::endl;
		_Request_content = handle_alias(Conf.Server_par[0].Loc[index_loc].alias, loc);
	}
	if (loc == "cgi-bin/" || _Request_content.find("cgi-bin/") >= 0)
		check_cgi();
	//if (autoindex == "on") a faire
	// if (check_vectors(Conf.Server_par[0].Loc[index_loc].methods, _Request_type) != 1)
	// 	return (print_logs("Client", "Unothorized method", 2), 404);

	return (0);
}