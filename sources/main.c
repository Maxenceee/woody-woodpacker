/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:07:36 by mbrement          #+#    #+#             */
/*   Updated: 2024/04/24 15:45:42 by mbrement         ###   ########lyon.fr   */
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
	if (!reader)
	{
		printf("Error: Cannot read file %s\n", av[1]);
		return (1);
	}

	if (reader->get_uint8(reader) != 0x7F)
	{
		delete_binary_reader(reader);
		printf("Error: File %s is not an ELF file\n", av[1]);
		return (1);
	}

	// Skip the first byte of the file (check before)
	// reader->get_uint8(reader) != 0x7F
	
	// Get the file e_type reading 3 bytes as a string
	t_file_format *file_format = new_file_format(reader);
	if (file_format == NULL)
	{
		printf("Error: Cannot get format for file %s\n", av[1]);
		return (1);
	}
	printf("File e_type: '%s' with %i bits, %s, e_type of file: %s, e_entry: %p\n", file_format->e_ident_mag, file_format->e_ident_class, file_format->e_ident_data_type, file_format->e_type_name, file_format->e_entry);
	printf("Offset of programm header: %ld\n", file_format->e_shoff);
	printf("Offset of section header : %ld\n", file_format->e_phoff); 
	printf("Header size              : %ld\n", file_format->e_ehsize); 
	printf("e_phentsize              : %d\n", file_format->e_phentsize); 
	printf("e_phnum                  : %d\n", file_format->e_phnum); 
	printf("e_shentsize              : %d\n", file_format->e_shentsize); 
	printf("e_shnum                  : %d\n", file_format->e_shnum); 
	// size_t str = reader->get_date(reader);
	// printf("Date: '%zu'\n", str);
	// free(file_format);
	// free(reader);
	delete_binary_reader(reader);
	delete_file_format(file_format);
}
