/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bw_set_bytes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 12:34:23 by mgama             #+#    #+#             */
/*   Updated: 2024/06/29 12:35:16 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "writer/binary_writer.h"

void	bw_set_bytes(t_binary_writer *this, uint8_t *data, uint32_t length)
{
	for (size_t i = 0; i < length; i++)
		this->set_uint8(this, data[i]);
}
