/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:13:01 by mgama             #+#    #+#             */
/*   Updated: 2024/07/16 19:14:22 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void *ft_memmove(void *dst, const void *src, size_t n)
{
	uint8_t *d = (uint8_t *)dst;
	const uint8_t *s = (const uint8_t *)src;

	if (dst == src || n == 0)
		return (dst);

	if (s < d && d < s + n) {
		d += n;
		s += n;
		while (n--)
			*(--d) = *(--s);
	} else {
		while (n--)
			*d++ = *s++;
	}

	return (dst);
}
