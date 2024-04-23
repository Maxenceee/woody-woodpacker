/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   br_get_uint16.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 22:28:10 by mgama             #+#    #+#             */
/*   Updated: 2024/04/23 12:15:19 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader/binary_reader.h"

uint16_t	br_get_uint16(t_binary_reader *this)
{
	return (((this->get_uint8(this) << 8) | this->get_uint8(this)) >> 0);
}
