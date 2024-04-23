/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_reader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 20:06:45 by mgama             #+#    #+#             */
/*   Updated: 2024/04/23 14:11:02 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "binary_reader.h"

void	init_binary_reader(t_binary_reader *reader)
{
	reader->seek = &br_seek;
	reader->tell = &br_tell;
	reader->get_uint8 = &br_get_uint8;
	reader->get_uint16 = &br_get_uint16;
	reader->get_uint32 = &br_get_uint32;
	reader->get_int16 = &br_get_int16;
	reader->get_int32 = &br_get_int32;
	reader->get_fword = &br_get_fword;
	reader->get_2dot14 = &br_get_2dot14;
	reader->get_fixed = &br_get_fixed;
	reader->get_string = &br_get_string;
	reader->get_unicode_string = &br_get_unicode_string;
	reader->get_date = &br_get_date;
	reader->slice = &br_slice;
}

void	delete_binary_reader(t_binary_reader *this)
{
	if (!this)
		return ;
	if (this->data)
		free(this->data);
	free(this);
	this = NULL;
}

t_binary_reader	*new_binary_reader(int fd)
{
	t_binary_reader	*reader;

	reader = ft_calloc(1, sizeof(t_binary_reader));
	if (!reader)
		return (ft_error(WD_PREFIX"Could not allocate memory.\n"), NULL);
	reader->data = ft_read_file(fd, reader->data, &reader->size);
	if (!reader->data)
		return (free(reader), ft_error(WD_PREFIX"Could not allocate memory.\n"), NULL);
	init_binary_reader(reader);
	return (reader);
}
