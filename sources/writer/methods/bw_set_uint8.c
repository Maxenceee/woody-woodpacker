/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bw_set_uint8.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 12:27:52 by mgama             #+#    #+#             */
/*   Updated: 2024/06/29 12:30:19 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "writer/binary_writer.h"

void	bw_set_uint8(t_binary_writer *this, uint8_t value)
{
	if (this->_pos >= this->size)
		return ;
	this->data[this->_pos++] = value;
}
