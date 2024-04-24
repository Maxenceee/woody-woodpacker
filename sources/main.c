/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:07:36 by mbrement          #+#    #+#             */
/*   Updated: 2024/04/24 17:12:53 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	
	// Get the file e_type reading 3 bytes as a string
	t_elf_file *file_format = new_elf_file(reader);
	if (file_format == NULL)
	{
		printf("Error: Cannot get format for file %s\n", av[1]);
		return (1);
	}

	print_elf_file(file_format);

	delete_binary_reader(reader);
	delete_elf_file(file_format);
}
