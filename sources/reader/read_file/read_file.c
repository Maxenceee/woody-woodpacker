/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 21:46:34 by mgama             #+#    #+#             */
/*   Updated: 2024/07/12 22:38:54 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reader/binary_reader.h"

unsigned char	*ft_read_file(int fd, unsigned char *file, uint64_t *rsize)
{
	unsigned char	*buff;
	int				read_bytes;
	uint64_t		size;

	size = 0;
	buff = ft_calloc((BUFFER_SIZE + 1), sizeof(unsigned char));
	if (!buff)
		return (NULL);
	read_bytes = 1;
	lseek(fd, 0, SEEK_SET);
	while (read_bytes != 0)
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes == -1)
			return (free(buff), NULL);
		buff[read_bytes] = '\0';
		file = ft_memjoin(file, buff, size, read_bytes);
		if (!file)
			return (free(buff), NULL);
		size += read_bytes;
	}
	*rsize = size;
	free(buff);
	return (file);
}
