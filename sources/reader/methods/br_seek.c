/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   br_seek.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 22:21:24 by mgama             #+#    #+#             */
/*   Updated: 2024/07/02 19:14:25 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader/binary_reader.h"

uint64_t	br_seek(t_binary_reader *this, uint64_t pos)
{
	uint64_t	old_pos;

	old_pos = this->_pos;
	this->_pos = pos;
	return (old_pos);
}
