/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   br_get_uint8.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 22:25:54 by mgama             #+#    #+#             */
/*   Updated: 2024/05/13 16:43:10 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader/binary_reader.h"

uint8_t	br_get_uint8(t_binary_reader *this)
{
	if (this->_pos >= this->size)
		return (0);
	return (this->data[this->_pos++]);
}
