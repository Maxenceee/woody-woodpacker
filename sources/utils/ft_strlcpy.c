/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:00:27 by mgama             #+#    #+#             */
/*   Updated: 2023/10/10 15:39:34 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_strlcpy(char *dest, char *src, uint32_t size)
{
	uint32_t	i;
	uint32_t	x;

	x = ft_strlen(src);
	i = 0;
	if (size != 0)
	{
		while (i < size && src[i] != '\0')
		{
			dest[i] = src[i];
			i++;
		}
	}
	return (x);
}
