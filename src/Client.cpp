/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbled <nbled@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 02:19:32 by nbled             #+#    #+#             */
/*   Updated: 2023/12/13 16:55:07 by tchantro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client() : _channel(NULL)
{}

Client::~Client()
{}

int		Client::GetSocket(void)
{
	 return (_socket);
}

void	Client::SetSocket(int socket)
{
	_socket = socket;
}

Channel*	Client::getChannel(void)
{
	return (this->_channel);
}

void	Client::setChannel(Channel *chan)
{
	_channel = chan;
}
