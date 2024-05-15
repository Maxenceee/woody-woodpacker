/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   br_get_bytes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 14:00:32 by mgama             #+#    #+#             */
/*   Updated: 2024/05/11 14:03:37 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader/binary_reader.h"

size_t	br_get_bytes(t_binary_reader *this, char *target, size_t length)
{
	size_t	i = 0;

	if (!target)
		return (i);

	for (; i < length; i++)
	{
		target[i] = this->get_uint8(this);
	}
	return (i);
}
