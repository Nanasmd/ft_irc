/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbled <nbled@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 02:19:28 by nbled             #+#    #+#             */
/*   Updated: 2023/12/13 16:23:49 by tchantro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <string>
#include <vector>

#include "Client.hpp"

class Client;

class Channel
{
    public:
        Channel();
        Channel(std::string name);
        ~Channel();

		std::string				getName(void) const;
		std::vector<Client*>&	getClient(void);

	private:
		std::vector<Client*>    _clients;
        std::string             _name;
};

#endif
