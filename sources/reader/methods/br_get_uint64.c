/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   br_get_uint64.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:43:44 by mbrement          #+#    #+#             */
/*   Updated: 2024/05/07 14:51:38 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "reader/binary_reader.h"

uint64_t	br_get_uint64(t_binary_reader *this)
{
	if (this->endian == READER_LITTLE_ENDIAN)
	{
		return (this->get_uint32(this) | ((uint64_t)this->get_uint32(this) << 32));
	}
	return (((uint64_t)this->get_uint32(this) << 32) | this->get_uint32(this));
}
