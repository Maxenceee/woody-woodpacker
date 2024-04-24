/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   br_get_uint32.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 22:32:17 by mgama             #+#    #+#             */
/*   Updated: 2024/04/24 14:02:50 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader/binary_reader.h"

uint32_t	br_get_uint32(t_binary_reader *this)
{
	if (this->endian == READER_LITTLE_ENDIAN)
	{
		return ((this->get_uint8(this))
			| (this->get_uint8(this) << 8)
			| (this->get_uint8(this) << 16)
			| (this->get_uint8(this) << 24));
	}
	return ((this->get_uint8(this) << 24)
		| (this->get_uint8(this) << 16)
		| (this->get_uint8(this) << 8)
		| (this->get_uint8(this)));
}
