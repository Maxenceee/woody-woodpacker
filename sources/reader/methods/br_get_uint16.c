/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   br_get_uint16.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 22:28:10 by mgama             #+#    #+#             */
/*   Updated: 2024/04/24 14:02:41 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader/binary_reader.h"

uint16_t	br_get_uint16(t_binary_reader *this)
{
	if (this->endian == READER_LITTLE_ENDIAN)
	{
		return ((this->get_uint8(this) | this->get_uint8(this)) << 8);
	}
	return ((this->get_uint8(this) << 8) | this->get_uint8(this));
}
