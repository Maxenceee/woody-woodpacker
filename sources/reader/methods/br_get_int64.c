/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   br_get_int64.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:46:17 by mbrement          #+#    #+#             */
/*   Updated: 2024/04/23 16:58:10 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "reader/binary_reader.h"

int64_t	br_get_int64(t_binary_reader *this)
{
	return (((long)this->get_uint8(this) << 56)
		| ((long)this->get_uint8(this) << 48)
		| ((long)this->get_uint8(this) << 40)
		| ((long)this->get_uint8(this) << 32)
		| (this->get_uint8(this) << 24)
		| (this->get_uint8(this) << 16)
		| (this->get_uint8(this) << 8)
		| (this->get_uint8(this)));
}
