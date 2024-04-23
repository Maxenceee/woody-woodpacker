/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ljoin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:49:53 by mgama             #+#    #+#             */
/*   Updated: 2023/12/05 14:32:34 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*ft_ljoin(void *s1, void *s2,
	unsigned int size, unsigned int length)
{
	void	*str;

	if (!s1)
		s1 = (void *)malloc(sizeof(void *));
	if (!s1)
		return (NULL);
	if (!s2)
		return (free(s1), NULL);
	str = malloc(sizeof(void) * (size + length));
	if (!str)
		return (free(s1), NULL);
	ft_memcpy(str, s1, size);
	ft_memcpy(str + size, s2, length);
	free(s1);
	return (str);
}
