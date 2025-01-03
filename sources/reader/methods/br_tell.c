/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   br_tell.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 22:24:41 by mgama             #+#    #+#             */
/*   Updated: 2024/07/02 19:15:33 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader/binary_reader.h"

uint64_t	br_tell(t_binary_reader *this)
{
	return (this->_pos);
}
