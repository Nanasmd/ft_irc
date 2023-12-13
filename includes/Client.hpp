/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbled <nbled@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 02:19:28 by nbled             #+#    #+#             */
/*   Updated: 2023/12/13 16:56:55 by tchantro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "Channel.hpp"

class Channel;

class Client
{
    public:
        Client();
        ~Client();

		int		GetSocket(void);
		Channel*	getChannel(void);
		void	SetSocket(int socket);
		void	setChannel(Channel *chan);

	private:
		Channel* _channel;
		int	_socket;
};

#endif
