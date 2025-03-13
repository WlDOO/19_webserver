/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logs.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:18:44 by armitite          #+#    #+#             */
/*   Updated: 2025/03/13 16:37:04 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

void	Server::print_logs(std::string user, std::string message, int code) {

	if (!user.empty())
		std::cout << BLUE << "[" << user << "]" << RESET << " : ";
	if (code == 1)
		std::cout << GREEN << message << RESET << " " << std::endl;
	if (code == 2)
		std::cout << RED << message << RESET << " " << std::endl;

	return ;
}