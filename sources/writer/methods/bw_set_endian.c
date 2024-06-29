/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bw_set_endian.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 12:35:20 by mgama             #+#    #+#             */
/*   Updated: 2024/06/29 12:35:40 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "writer/binary_writer.h"

void	bw_set_endian(t_binary_writer *this, int endian)
{
	this->endian = endian;
}
