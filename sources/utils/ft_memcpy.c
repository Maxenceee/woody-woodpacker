/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:16:53 by mgama             #+#    #+#             */
/*   Updated: 2023/10/22 20:27:37 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	void	*lst_dst;

	if (n == 0 || dst == src)
		return (dst);
	i = 0;
	lst_dst = dst;
	while (i < n)
	{
		((char *)dst)[i] = ((char *)src)[i];
		i++;
	}
	return (lst_dst);
}
