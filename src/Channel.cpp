/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbled <nbled@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 02:19:32 by nbled             #+#    #+#             */
/*   Updated: 2023/12/13 16:23:59 by tchantro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel()
{}

Channel::Channel(std::string name) : _name(name)
{}

Channel::~Channel()
{}

std::string		Channel::getName(void) const
{
	return (this->_name);
}

std::vector<Client*>&	Channel::getClient(void)
{
	return (this->_clients);
}
