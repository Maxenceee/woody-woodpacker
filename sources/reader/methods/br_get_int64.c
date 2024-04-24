/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   br_get_int64.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:46:17 by mbrement          #+#    #+#             */
/*   Updated: 2024/04/24 14:05:22 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader/binary_reader.h"

int64_t	br_get_int64(t_binary_reader *this)
{
	if (this->endian == READER_LITTLE_ENDIAN)
	{
		return (this->get_uint32(this) | ((uint64_t)this->get_uint32(this) << 32));
	}
	return (((uint64_t)this->get_uint32(this) << 32) | this->get_uint32(this));
}
