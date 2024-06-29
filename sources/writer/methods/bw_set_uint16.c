/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bw_set_uint16.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 12:28:26 by mgama             #+#    #+#             */
/*   Updated: 2024/06/29 12:31:52 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "writer/binary_writer.h"

void	bw_set_uint16(t_binary_writer *this, uint16_t value)
{
	if (this->endian == WRITER_LITTLE_ENDIAN)
	{
		this->set_uint8(this, value & 0xFF);
		this->set_uint8(this, (value >> 8) & 0xFF);
	}
	else
	{
		this->set_uint8(this, (value >> 8) & 0xFF);
		this->set_uint8(this, value & 0xFF);
	}
}
