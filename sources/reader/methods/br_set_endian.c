/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   br_set_endian.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:58:41 by mgama             #+#    #+#             */
/*   Updated: 2024/04/24 13:58:58 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader/binary_reader.h"

void	br_set_endian(t_binary_reader *this, int endian)
{
	this->endian = endian;
}
