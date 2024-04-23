/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   br_get_int64.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:46:17 by mbrement          #+#    #+#             */
/*   Updated: 2024/04/23 17:43:13 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader/binary_reader.h"

int64_t	br_get_int64(t_binary_reader *this)
{
	return (((uint64_t)this->get_uint32(this) << 32) | this->get_uint32(this));
}
