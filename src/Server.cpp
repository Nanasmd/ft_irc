/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbled <nbled@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 02:19:32 by nbled             #+#    #+#             */
/*   Updated: 2023/12/13 16:55:43 by tchantro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "Server.hpp"

#define BUFFER_SIZE 1024
#define MAX_CONNECTIONS 10

// ----------------------------------------------------------------------
//                                 INIT
// ----------------------------------------------------------------------

Server::Server(const std::string &port, const std::string &pwd) : _port(port), _pwd(pwd)
{
	return ;
}

Server::~Server(void)
{
	return ;
}

void	Server::ServerInit(void)
{
	_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (_serverSocket == -1)
		throw SocketException();
	sockaddr_in	serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(atoi(_port.c_str()));
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(_serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1)
		throw BindException();
	if (listen(_serverSocket, MAX_CONNECTIONS) == -1)
		throw ListenException();
	std::cout << "Server listening on port " << _port << std::endl;
}

// ----------------------------------------------------------------------
//                             HANDLE MESSAGE
// ----------------------------------------------------------------------

void Server::SendMessage(int Socket, std::string message)
{
    char *response = strdup(message.c_str());
    send(Socket, response, strlen(response), 0);
    std::cout << message;
}

void Server::ChannelCreate(int senderSocket, const char *message)
{
	if (strncmp(message, "/create", 7) == 0)
	{
        if (strlen(message) > 9)
        {
            std::string name(message);
            Channel newChannel(name.substr(8, strlen(message) - 9));
            _channels.push_back(newChannel);
            SendMessage(senderSocket, "CHANNEL \"" + newChannel.getName() + "\" CREATED\n");
        }
        else
            SendMessage(senderSocket, "CHANNEL MUST HAVE A NAME\n");
    }
}

void Server::ChannelList(int senderSocket)
{
    for (std::vector<Channel>::iterator it = _channels.begin(); it != _channels.end(); ++it)
        SendMessage(senderSocket, it->getName() + "\n");
}

void Server::ChannelJoin(int senderSocket, const char *message)
{
	if (strlen(message) > 7)
    {
        std::string name(message);
        name = name.substr(6, strlen(message) - 7);
        for (std::vector<Client>::iterator sender = _clients.begin(); sender != _clients.end(); ++sender)
        {
            if (sender->GetSocket() == senderSocket)
            {
                for (std::vector<Channel>::iterator it = _channels.begin(); it != _channels.end(); ++it)
                {
                    if (it->getName() == name)
                    {
                        //sender->getChannel() = &(*it);
						sender->setChannel(&(*it));
                        it->getClient().push_back(&(*sender));
                        SendMessage(senderSocket, "SERVER "+name+" joined\n");
                    }
                }
            }
        }
    }
    else
        SendMessage(senderSocket, "FAIL JOINING CHANNEL\n");
}

void Server::HandleCommand(int senderSocket, const char *message)
{
	if (strncmp(message, "/create", 7) == 0)
	{
        ChannelCreate(senderSocket, message);
    }
	else if (strncmp(message, "/list", 5) == 0 && strlen(message) == 6)
    {
        ChannelList(senderSocket);
    }
	else if (strncmp(message, "/join", 5) == 0)
    {
        ChannelJoin(senderSocket, message);
    }
    else
        SendMessage(senderSocket, "COMMAND NOT FOUND\n");
}

void Server::HandleMessage(int senderSocket, const char *message, size_t messageLength)
{
	if (strncmp(message, "/", 1) == 0)
        HandleCommand(senderSocket, message);
	else
    {
        for (std::vector<Client>::iterator sender = _clients.begin(); sender != _clients.end(); ++sender)
        {
            if (sender->GetSocket() == senderSocket)
            {
                if (sender->getChannel())
                {
                    Channel* channel = sender->getChannel();
                    for (std::vector<Client*>::iterator it = channel->getClient().begin(); it != channel->getClient().end(); ++it)
                    {
                        send((*it)->GetSocket(), message, messageLength, 0);
                    }
                    std::cout << "channel "<< channel->getName() << ": " << message;
                }
            }
        }
    }
}

// ----------------------------------------------------------------------
//                             SERVER LOOP
// ----------------------------------------------------------------------

void Server::ServerLoop(void)
{
	// Select var init
    fd_set masterSet;
    FD_ZERO(&masterSet);
    FD_SET(_serverSocket, &masterSet);
    int maxSocket = _serverSocket;

    while (true)
    {
		// Select
        fd_set readSet = masterSet;
        if (select(maxSocket + 1, &readSet, NULL, NULL, NULL) == -1)
        {
            std::cerr << "Error in select()\n";
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i <= maxSocket; ++i)
        {
            if (FD_ISSET(i, &readSet))
            {
                if (i == _serverSocket)
                {
                    // Accept incoming connections
                    sockaddr_in clientAddr;
                    socklen_t clientAddrLen = sizeof(clientAddr);
                    int clientSocket = accept(_serverSocket, (struct sockaddr *)&clientAddr, &clientAddrLen);
                    if (clientSocket == -1)
                    {
                        std::cerr << "Error accepting connection\n";
                        continue;
                    }
                    std::cout << "Client connected\n";
                    FD_SET(clientSocket, &masterSet);
                    if (clientSocket > maxSocket)
                        maxSocket = clientSocket;
                    // Add the new client to the global vector
                    Client newClient;
                    newClient.SetSocket(clientSocket);
                    _clients.push_back(newClient);
                }
                else
                {
                    // Handle data from an existing client
                    char buffer[BUFFER_SIZE];
                    bzero(buffer, BUFFER_SIZE);
                    ssize_t bytesRead = recv(i, buffer, sizeof(buffer), 0);
					// Handle end of communications
                    if (bytesRead <= 0)
                    {
                        if (bytesRead == 0)
                            std::cout << "Client disconnected\n";
                        else
                            std::cerr << "Error receiving data\n";

                        close(i);
                        FD_CLR(i, &masterSet);

                        // Remove the client from the global vector
                        for (std::vector<Client>::iterator it = _clients.begin(); it != _clients.end(); ++it)
                        {
                            if (it->GetSocket() == i)
                            {
                                _clients.erase(it);
                                break;
                            }
                        }
                    }
					// Process
                    else
                        HandleMessage(i, buffer, bytesRead);
                }
            }
        }
    }
}

/*int		Server::getSocket(void)
{
	return (this->_serverSocket);
}*/

const char*	Server::SocketException::what() const throw()
{
	return ("Error creating socket");
}

const char*	Server::BindException::what() const throw()
{
	return ("Error binding socket");
}

const char*	Server::ListenException::what() const throw()
{
	return ("Error listening for connections");
}
