/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   br_get_int16.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 22:34:29 by mgama             #+#    #+#             */
/*   Updated: 2024/04/23 12:15:12 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader/binary_reader.h"

int16_t	br_get_int16(t_binary_reader *this)
{
	int16_t	res;

	res = this->get_uint16(this);
	if (res & 0x8000)
		res -= (1 << 16);
	return (res);
}
