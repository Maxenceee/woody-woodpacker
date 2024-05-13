/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:07:36 by mbrement          #+#    #+#             */
/*   Updated: 2024/05/13 16:32:29 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "AES/aes.h"
#include "woody.h"
#include <stdint.h>

int	main(int ac, char **av)
{






	int file_id ;
	file_id = 1;

	if (ac > 2 && av[1][0] == '-' && av[1][1] == 'e'){
		file_id = 2;
		int tmp_fd = open(av[file_id], O_RDONLY);
		t_binary_reader *reader_tmp = new_binary_reader(tmp_fd);
		if (!reader_tmp)
		{
			printf("Error: Cannot read file %s\n", av[1]);
			return (1);
		}
		uint8_t tm[65];
		for (int i = 0; i < 64; i++)
			tm[i] = reader_tmp->get_uint8(reader_tmp);
		tm[65] = 0;
		char *tmp = calloc(1, 256);
		BytesToString(tm, tmp);
		// printf("init    : ");
		// for(int i = 0; i < 16; i++)
		// 	printf("%02x", tmp[i]);
		// printf("\n");
		uint8_t **encoded = AES_encrypt(tmp, av[3]);
	if (encoded == NULL)
	{
		printf("error\n");
		return(0);
	}
	// printf("encoded : ");
    // for(int i = 0; i < 16; i++){
    //     printf("%02x", (*encoded)[i]);
    // }
	// printf("\n");
	else if (ac > 2 && av[1][0] == '-' && av[1][1] == 'd'){
		file_id = 2;
		int tmp_fd = open(av[file_id], O_RDONLY);
		t_binary_reader *reader_tmp = new_binary_reader(tmp_fd);
		if (!reader_tmp)
		{
			printf("Error: Cannot read file %s\n", av[1]);
			return (1);
		}
		uint8_t tm[65];
		for (int i = 0; i < 64; i++)
			tm[i] = reader_tmp->get_uint8(reader_tmp);
		tm[65] = 0;
		char *tmp = calloc(1, 256);
		BytesToString(tm, tmp);
		// printf("init    : ");
		// for(int i = 0; i < 16; i++)
		// 	printf("%02x", tmp[i]);
		// printf("\n");
		uint8_t **decoded = AES_decrypt(tmp, av[3]);
		char *str = calloc(1, 256);
		printf("decoded : ");
	    for(int i = 0; i < 16; i++){
	        printf("%02x", (*decoded)[i]);
    }
	printf("\n");
	}
	else if (ac != 2)
	{
		printf("Usage: %s <file>\n", av[0]);
		return (1);
	}


	exit(1);
	
	

	int fd = open(av[file_id], O_RDONLY);
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

	/**
	 * We copy the content of the original elf file to the new one.
	 * This is done to keep the original file intact.
	 */
	t_elf_file *new_elf_file = malloc(sizeof(t_elf_file));
	if (!new_elf_file)
		return (ft_error(WD_PREFIX"Could not allocate memory.\n"), 1);
	ft_memcpy(new_elf_file, elf_file, sizeof(t_elf_file));

	packer(elf_file, new_elf_file, reader);

	delete_binary_reader(reader);
	delete_elf_file(elf_file);
}
