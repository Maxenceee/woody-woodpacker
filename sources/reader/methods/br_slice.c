/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   br_slice.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:21:29 by mgama             #+#    #+#             */
/*   Updated: 2024/04/23 12:15:47 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader/binary_reader.h"

t_binary_reader	*br_slice(t_binary_reader *this, uint32_t start,
	uint32_t length)
{
	t_binary_reader	*reader;

	reader = ft_calloc(1, sizeof(t_binary_reader));
	if (!reader)
		return (ft_error(WD_PREFIX"Could not allocate memory.\n"), NULL);
	reader->data = malloc(length * sizeof(char));
	if (!reader->data)
		return (free(reader), ft_error(WD_PREFIX"Could not allocate memory.\n"), NULL);
	ft_memcpy(reader->data, this->data + start, length);
	init_binary_reader(reader);
	return (reader);
}
