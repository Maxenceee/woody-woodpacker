/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   br_get_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:16:45 by mgama             #+#    #+#             */
/*   Updated: 2024/04/24 18:54:24 by mgama            ###   ########.fr       */
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

int	br_get_rstring(t_binary_reader *this, uint16_t max)
{
	char	i;
	int		j = 0;

	while ((i = this->get_uint8(this)) != 0 && j < max)
	{
		printf("%c", i);
		j++;
	}
	while (j < max)
	{
		printf(" ");
		j++;
	}
	return (j);
}
