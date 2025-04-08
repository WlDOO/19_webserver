/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse_request.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:35:41 by armitite          #+#    #+#             */
/*   Updated: 2025/04/04 04:33:41 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

int		Server::check_cgi(int index_loc) {

	std::size_t found;
	std::string ext;
	
	found = _Request_content.rfind(".");
	if (found == std::string::npos)
		return (1);
	ext = _Request_content.substr(found, _Request_content.size() - found);
	if (check_vectors(Conf.Server_par[0].Loc[index_loc].cgi_extonsions, ext) == 1) {

		//_Script_path = Conf.Server_par[0].root + _Request_content;
		_Script_path = "Bad";
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
	// size_t start;
	std::string loc;
	size_t i;
	int index_loc = -1;
	

	if (_Request_content == "asa.html" || _Request_content == "reve.html" || _Request_content.empty())
		return (0);
	if (_Request_content == "index.html" || _Request_content.empty())
	{	
		_Request_content = Conf.Server_par[0].index;
		return (0);
	}
	if (_Request_type == "DELETE")
		return (0);
	found = _Request_content.find("/");
	std::cout << _Request_content << std::endl;
	if (found == std::string::npos)
		return (1);
	loc = _Request_content.substr(0, found + 1);
	std::cout << "ici : " << loc << std::endl;
	for (i = 0; i < Conf.Server_par[0].Loc.size(); i++) {

		if (loc == Conf.Server_par[0].Loc[i].Location)
		{
			std::cout << "ok" << std::endl;
			index_loc = i;
			break ;
		}
		std::cout << "les loc : " << Conf.Server_par[0].Loc[i].Location << std::endl;
	}
	if (index_loc == -1)
		return (1);
	if (allowed_method(index_loc) == 1)
		return (1);
	// if (found != std::string::npos)
	// 	_Request_content = _Request_content.substr(start + 1);
	// std::cout << "PECPEC: " << _Request_content << std::endl;
	// if (!Conf.Server_par[0].Loc[index_loc].redirect_url.empty())
	// 	std::cout << Conf.Server_par[0].Loc[index_loc].redirect_url.empty() << std::endl;
	//std::cout << "la methode :" << Conf.Server_par[0].Loc[index_loc].methods[0] << std::endl;
	std::cout << "la loc :" << loc << std::endl;
	if (!Conf.Server_par[0].Loc[index_loc].alias.empty())
	{
		std::cout << Conf.Server_par[0].Loc[index_loc].alias << std::endl;
		_Request_content = handle_alias(Conf.Server_par[0].Loc[index_loc].alias, loc);
	}
	if (loc == "cgi-bin/") // || _Request_content.find("cgi-bin/") >= 0)
		check_cgi(index_loc);
	//if (autoindex == "on") a faire
	// if (check_vectors(Conf.Server_par[0].Loc[index_loc].methods, _Request_type) != 1)
	// 	return (print_logs("Client", "Unothorized method", 2), 404);

	return (0);
}