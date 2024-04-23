/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   br_get_int64.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:46:17 by mbrement          #+#    #+#             */
/*   Updated: 2024/04/23 17:28:43 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "reader/binary_reader.h"

int64_t	br_get_int64(t_binary_reader *this)
{
	return ((long)this->get_int32(this) << 32 | this->get_int32(this));
}
