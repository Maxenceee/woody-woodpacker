/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   br_get_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:16:45 by mgama             #+#    #+#             */
/*   Updated: 2024/07/17 22:32:41 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader/binary_reader.h"

char	*br_get_string(t_binary_reader *this, uint16_t length)
{
	int		i;
	char	*res;

	res = malloc((length + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = -1;
	while (++i < length)
		res[i] = this->get_uint8(this);
	res[i] = 0;
	return (res);
}

char	*br_get_rstring(t_binary_reader *this)
{
	uint8_t	c;
	uint8_t	*res;
	int		i = 0;

	res = ft_calloc(1, sizeof(char));
	if (!res)
		return (NULL);
	while ((c = this->get_uint8(this)) != 0)
	{
		res = ft_memjoin(res, &c, i, 1);
		if (!res)
			return (NULL);
		i++;
	}
	return ((char *)ft_memjoin(res, (uint8_t *)"\0", i, 1));
}
