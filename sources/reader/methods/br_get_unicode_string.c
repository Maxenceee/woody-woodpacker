/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   br_get_unicode_string.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:19:52 by mgama             #+#    #+#             */
/*   Updated: 2024/04/23 12:15:23 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader/binary_reader.h"

char	*br_get_unicode_string(t_binary_reader *this, uint16_t length)
{
	int		i;
	char	*res;

	res = ft_calloc(length + 1, sizeof(char));
	if (!res)
		return (NULL);
	i = -1;
	while (++i < length / 2)
		res[i] = this->get_uint16(this);
	return (res);
}
