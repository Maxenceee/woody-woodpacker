/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_gen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:18:17 by mgama             #+#    #+#             */
/*   Updated: 2024/07/18 14:28:39 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"
#include <time.h>

void	gen_aes_key(uint8_t *dest, size_t size)
{
	srand(time(0));

	if (size)
	{
		for (size_t n = 0; n < size; n++) {
			dest[n] = rand() % 256;
		}
	}
}
