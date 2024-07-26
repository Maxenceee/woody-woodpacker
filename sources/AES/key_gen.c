/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_gen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:18:17 by mgama             #+#    #+#             */
/*   Updated: 2024/07/26 18:39:31 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"
#include <time.h>
#include <sys/time.h>

void	gen_aes_key(uint8_t *dest, size_t size)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	srand(tv.tv_usec);

	if (size)
	{
		for (size_t n = 0; n < size; n++) {
			dest[n] = 33 + rand() % (126 + 1 - 33);
		}
	}
}
