/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:07:36 by mbrement          #+#    #+#             */
/*   Updated: 2024/04/23 16:42:41 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include "woody.h"

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		printf("Usage: %s <file>\n", av[0]);
		return (1);
	}

	int fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		printf("Error: Cannot open file %s\n", av[1]);
		return (1);
	}

	/**
	 * Create new reader
	 */
	t_binary_reader *reader = new_binary_reader(fd);
	if (!reader || reader->get_uint8(reader) != 0x7F)
	{
		printf("Error: Cannot read file %s\n", av[1]);
		return (1);
	}

	// Skip the first byte of the file (check before)
	// reader->get_uint8(reader) != 0x7F
	
	// Get the file type reading 3 bytes as a string
	struct s_file_Format *fileFormat = new_file_format(reader);
	if (fileFormat == NULL){
		printf("Error: Cannot get format for file %s\n", av[1]);
		return (1);
	}
	printf("File type: '%s' with %i bits, %s, type of file : %s, entry : %p\n", fileFormat->filetype, fileFormat->fileformat, fileFormat->endianness, fileFormat->type_Name, fileFormat->entry);
	// size_t str = reader->get_date(reader);
	// printf("Date: '%zu'\n", str);
	// free(fileFormat);
	// free(reader);
	delete_binary_reader(reader);
	delete_file_format(fileFormat);
}
