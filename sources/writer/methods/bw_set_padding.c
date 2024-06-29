/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bw_set_padding.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 12:35:46 by mgama             #+#    #+#             */
/*   Updated: 2024/06/29 12:36:13 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "writer/binary_writer.h"

void	bw_set_padding(t_binary_writer *this, uint32_t padsize)
{
	for (size_t i = 0; i < padsize; i++)
		this->set_uint8(this, 0);
}
