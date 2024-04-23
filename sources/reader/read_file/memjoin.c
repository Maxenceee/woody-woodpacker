/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memjoin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 16:47:15 by mgama             #+#    #+#             */
/*   Updated: 2024/04/23 12:14:59 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader/binary_reader.h"

unsigned char	*ft_memjoin(unsigned char *s1, unsigned char *s2,
	uint32_t size, uint32_t length)
{
	unsigned char	*str;

	if (!s1)
		s1 = (unsigned char *)malloc(sizeof(unsigned char));
	if (!s1)
		return (NULL);
	if (!s2)
		return (free(s1), NULL);
	str = malloc(sizeof(unsigned char) * (size + length));
	if (!str)
		return (free(s1), NULL);
	ft_memcpy(str, s1, size);
	ft_memcpy(str + size, s2, length);
	free(s1);
	return (str);
}
