/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_writer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 20:06:45 by mgama             #+#    #+#             */
/*   Updated: 2024/06/28 21:54:14 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "binary_writer.h"

void	init_binary_writer(t_binary_writer *reader)
{
	reader->seek = &bw_seek;
	reader->tell = &bw_tell;
	reader->set_uint8 = &bw_set_uint8;
	reader->set_uint16 = &bw_set_uint16;
	reader->set_uint32 = &bw_set_uint32;
	reader->set_uint64 = &bw_set_uint64;
	reader->set_int16 = &bw_set_int16;
	reader->set_int32 = &bw_set_int32;
	reader->set_int64 = &bw_set_int64;
	reader->set_string = &bw_set_string;
	reader->set_bytes = &bw_set_bytes;
	reader->set_endian = &bw_set_endian;
}

void	delete_binary_writer(t_binary_writer *this)
{
	if (!this)
		return ;
	if (this->data)
		free(this->data);
	free(this);
	this = NULL;
}

t_binary_writer	*new_binary_writer(uint8_t *buffer, uint32_t size)
{
	t_binary_writer	*reader;

	reader = ft_calloc(1, sizeof(t_binary_writer));
	if (!reader)
		return (NULL);
	init_binary_writer(reader);
	reader->data = malloc(size);
	if (!reader->data)
	{
		free(reader);
		return (NULL);
	}
	ft_memcpy(reader->data, buffer, size);
	reader->size = size;
	return (reader);
}
