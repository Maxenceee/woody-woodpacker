/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   br_get_bytes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 14:00:32 by mgama             #+#    #+#             */
/*   Updated: 2024/07/13 14:11:38 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader/binary_reader.h"

size_t	br_get_bytes(t_binary_reader *this, uint8_t *target, size_t length)
{
	size_t	i = 0;

	if (!target)
		return (i);
	if (this->_pos + length > this->size)
		length = this->size - this->_pos;

	for (; i < length; i++)
	{
		target[i] = this->get_uint8(this);
	}
	return (i);
}
