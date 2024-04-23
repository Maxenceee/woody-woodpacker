/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   br_get_date.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:25:39 by mgama             #+#    #+#             */
/*   Updated: 2024/04/23 12:15:06 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader/binary_reader.h"

uint64_t	br_get_date(t_binary_reader *this)
{
	uint64_t	mac_time;

	mac_time = this->get_uint32(this) * 0x100000000 + this->get_uint32(this);
	return (mac_time);
}
