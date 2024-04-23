/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   br_get_uint64.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:43:44 by mbrement          #+#    #+#             */
/*   Updated: 2024/04/23 16:57:11 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "reader/binary_reader.h"

uint64_t	br_get_uint64(t_binary_reader *this)
{
	return(((unsigned long)this->get_uint8(this) << 56)
		| ((unsigned long)this->get_uint8(this) << 48)
		| ((unsigned long)this->get_uint8(this) << 40)
		| ((unsigned long)this->get_uint8(this) << 32)
		| (this->get_uint8(this) << 24)
		| (this->get_uint8(this) << 16)
		| (this->get_uint8(this) << 8)
		| (this->get_uint8(this)));
}
