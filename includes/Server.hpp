/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbled <nbled@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 02:19:28 by nbled             #+#    #+#             */
/*   Updated: 2023/12/13 16:07:28 by tchantro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <vector>
#include <exception>
#include <string>
#include <cstring>
#include <algorithm>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include "Client.hpp"
#include "Channel.hpp"

class Client;

class Server
{
    public:
        Server(const std::string &port, const std::string &pwd);
        ~Server();

		void ServerInit(void);
		// ----------------------------------------------------------------------
		//                            HANDLE MESSAGE
		// ----------------------------------------------------------------------
		void SendMessage(int Socket, std::string message);
		void ChannelCreate(int senderSocket, const char *message);
		void ChannelList(int senderSocket);
		void ChannelJoin(int senderSocket, const char *message);
		void HandleCommand(int senderSocket, const char *message);
		void HandleMessage(int senderSocket, const char *message, size_t messageLength);

		// ----------------------------------------------------------------------
		//                             SERVER LOOP
		// ----------------------------------------------------------------------

		void ServerLoop(void);

		// ----------------------------------------------------------------------
		//                            EXCEPTIONS
		// ----------------------------------------------------------------------
		
		class	SocketException : public std::exception
		{
			const char*		what() const throw();
		};

		class	BindException : public std::exception
		{
			const char*		what() const throw();
		};

		class	ListenException : public std::exception
		{
			const char*		what() const throw();
		};

		//int		getSocket(void) const;
	private:
		std::vector<Client> _clients;
		std::vector<Channel> _channels;
		std::string		_port;
		std::string		_pwd;
		int				_serverSocket;
};

#endif
