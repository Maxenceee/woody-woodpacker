/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   br_seek.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 22:21:24 by mgama             #+#    #+#             */
/*   Updated: 2024/04/23 12:15:25 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader/binary_reader.h"

uint32_t	br_seek(t_binary_reader *this, uint32_t pos)
{
	uint32_t	old_pos;

	old_pos = this->_pos;
	this->_pos = pos;
	return (old_pos);
}
