/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bw_seek.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 12:25:24 by mgama             #+#    #+#             */
/*   Updated: 2024/07/02 19:15:02 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "writer/binary_writer.h"

uint64_t	bw_seek(t_binary_writer *this, uint64_t pos)
{
	uint64_t	old_pos;

	old_pos = this->_pos;
	this->_pos = pos;
	return (old_pos);
}
