/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbled <nbled@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 02:19:28 by nbled             #+#    #+#             */
/*   Updated: 2023/12/13 17:01:05 by tchantro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Client.hpp"
#include "Server.hpp"

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cerr << "Error server arguments" << std::endl;
		return (1);
	}
	const std::string		port(argv[1]);
	const std::string		pwd(argv[2]);

	Server	test(port, pwd);

	try
	{
		test.ServerInit();
		test.ServerLoop();
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return (0);
}
