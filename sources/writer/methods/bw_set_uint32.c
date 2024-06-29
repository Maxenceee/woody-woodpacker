/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bw_set_uint32.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 12:28:31 by mgama             #+#    #+#             */
/*   Updated: 2024/06/29 12:31:51 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "writer/binary_writer.h"

void	bw_set_uint32(t_binary_writer *this, uint32_t value)
{
	if (this->endian == WRITER_LITTLE_ENDIAN)
	{
		this->set_uint16(this, value & 0xFFFF);
		this->set_uint16(this, (value >> 16) & 0xFFFF);
	}
	else
	{
		this->set_uint16(this, (value >> 16) & 0xFFFF);
		this->set_uint16(this, value & 0xFFFF);
	}
}
