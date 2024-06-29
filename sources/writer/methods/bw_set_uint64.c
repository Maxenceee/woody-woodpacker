/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bw_set_uint64.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 12:28:24 by mgama             #+#    #+#             */
/*   Updated: 2024/06/29 12:32:02 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "writer/binary_writer.h"

void	bw_set_uint64(t_binary_writer *this, uint64_t value)
{
	if (this->endian == WRITER_LITTLE_ENDIAN)
	{
		this->set_uint32(this, value & 0xFFFFFFFF);
		this->set_uint32(this, (value >> 32) & 0xFFFFFFFF);
	}
	else
	{
		this->set_uint32(this, (value >> 32) & 0xFFFFFFFF);
		this->set_uint32(this, value & 0xFFFFFFFF);
	}
}
