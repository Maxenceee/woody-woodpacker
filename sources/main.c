/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:07:36 by mbrement          #+#    #+#             */
/*   Updated: 2024/05/13 19:17:47 by mgama            ###   ########.fr       */
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
	
	// Get the file e_type reading 3 bytes as a string
	t_elf_file *elf_file = new_elf_file(reader);
	if (elf_file == NULL)
	{
		printf("Error: Cannot get format for file %s\n", av[1]);
		return (1);
	}

	print_elf_file(elf_file);

	printf("=================+++++=====\n%#x %#llx\n", _payload_64, _payload_size_64);

	/**
	 * We copy the content of the original elf file to the new one.
	 * This is done to keep the original file intact.
	 */
	// t_elf_file *new_elf_file = malloc(sizeof(t_elf_file));
	// if (!new_elf_file)
	// 	return (ft_error(WD_PREFIX"Could not allocate memory.\n"), 1);
	// ft_memcpy(new_elf_file, elf_file, sizeof(t_elf_file));

	// packer(elf_file, new_elf_file, reader);

	// delete_binary_reader(reader);
	// delete_elf_file(elf_file);
	// delete_elf_file(new_elf_file);
}
