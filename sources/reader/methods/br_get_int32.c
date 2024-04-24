/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   br_get_int32.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 22:36:55 by mgama             #+#    #+#             */
/*   Updated: 2024/04/24 14:05:08 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader/binary_reader.h"

int32_t	br_get_int32(t_binary_reader *this)
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
