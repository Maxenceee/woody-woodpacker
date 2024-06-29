/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bw_set_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 12:32:42 by mgama             #+#    #+#             */
/*   Updated: 2024/06/29 12:34:17 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "writer/binary_writer.h"

void	bw_set_string(t_binary_writer *this, const char *value)
{
	for (size_t i = 0; i < ft_strlen(value); i++)
		this->set_uint8(this, value[i]);
}
