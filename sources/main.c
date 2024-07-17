/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:07:36 by mbrement          #+#    #+#             */
/*   Updated: 2024/07/17 22:31:22 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

uint8_t key_aes[] = "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef";

static void	usage(void)
{
	// (void)fprintf(stderr, "%s\n", "usage: woody_woodpacker [-h] [-l] [-S] [-s] [-d] [-g] [-k key] file");
	(void)fprintf(stderr, "%s\n", "usage: woody_woodpacker <option(s)> file");
	(void)fprintf(stderr, "  %s\n", "Options are:");
	(void)fprintf(stderr, "  %-8s %s\n", "-h", "Display the ELF file header");
	(void)fprintf(stderr, "  %-8s %s\n", "-l", "Display the program headers");
	(void)fprintf(stderr, "  %-8s %s\n", "-S", "Display the sections' header");
	(void)fprintf(stderr, "  %-8s %s\n", "-s", "Display the symbol table");
	(void)fprintf(stderr, "  %-8s %s\n", "-d", "Display the section data");
	(void)fprintf(stderr, "  %-8s %s\n", "-g", "Update debug symbols");
	(void)fprintf(stderr, "  %-8s %s\n", "-k <key>", "Use custom encrypt key");
	exit(64);
}

int	main(int ac, char **av)
{
	char *target;
	int ch, option = 0;

	while ((ch = ft_getopt(ac, av, "k:hSdsln")) != -1) {
		switch (ch) {
			case 'k':
				option |= F_KEY;
				ft_memmove(key_aes, optarg, 32);
				break;
			case 'h':
				option |= F_HEADER;
				break;
			case 'l':
				option |= F_PROG;
				break;
			case 'S':
				option |= F_SECTION;
				break;
			case 'd':
				option |= F_DATA;
				break;
			case 's':
				option |= F_SYM;
				break;
			case 'g':
				option |= F_UDSYM;
				break;
			case 'n':
				option |= F_NOOUTPUT;
				break;
			default:
				usage();
		}
	}

	if (ac - optind != 1)
		usage();
	target = av[optind];

	int fd = open(target, O_RDONLY);
	if (fd == -1)
	{
		printf("Error: Cannot open file %s\n", target);
		return (1);
	}

	/**
	 * Create new reader
	 */
	t_binary_reader *reader = new_binary_reader(fd);
	if (!reader)
	{
		printf("Error: Cannot read file %s\n", target);
		return (1);
	}
	// Get the file e_type reading 3 bytes as a string
	t_elf_file *elf_file = new_elf_file(reader);
	if (elf_file == NULL)
	{
		delete_binary_reader(reader);
		return (1);
	}

	if (option & F_HEADER)
	{
		print_elf_file(elf_file, PELF_HEADER);
	}

	if (option & F_SECTION)
	{
		print_elf_file(elf_file, PELF_SECTION);
	}

	if (option & F_PROG)
	{
		print_elf_file(elf_file, PELF_PROG);
	}

	if (option & F_SYM)
	{
		print_elf_file(elf_file, PELF_SYM);
	}
	
	if (option & F_DATA)
	{
		print_elf_file(elf_file, PELF_DATA);
	}

	printf("================================================\n");
	printf("Target: %s\n", target);
	printf("Key: %s\n", key_aes);
	printf("================================================\n");

	/**
	 * INFO:
	 * ne pas supprimer c'est la version complete du chiffrement !!!
	 */

	// int csize = (reader->size + reader->size % 256);
	// unsigned char *cypher = ft_calloc(1, sizeof(unsigned char) * csize);
	// unsigned char *f_key = calloc(1, sizeof(unsigned char) * 256);

	// AES_256_Key_Expansion((unsigned char *)key, f_key);
	// int i = -1;
	// while (f_key[++i]) printf("%02x ", f_key[i]);
	// printf("\n");
	// printf("%i\n", csize%256);

	// unsigned char nonce[4] = {0x00, 0xFA, 0xAC, 0x24};
	// unsigned char IV[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00};
	
	// AES_CTR_encrypt((unsigned char *)reader->data, cypher, IV , nonce, reader->size, f_key, 64);
	// int iiii = open("res", O_CREAT | O_RDWR | O_TRUNC, 0755);
	// i = -1;
	// while (++i < reader->size)
	// 	dprintf(iiii, "%c", cypher[i]);

	// t_binary_reader *reader2 = new_binary_reader(iiii);

	// i = -1;
	// // printf("'");
	// // while (++i < csize)
	// // 	printf("%02x ", cypher[i]);
	// // printf("'\n");
	// csize = (reader2->size + reader2->size % 256);
	// printf("%i\n", csize);
	// unsigned char *res = malloc(csize);
	
	// AES_CTR_encrypt(cypher, res, IV , nonce, reader2->size, f_key, 64);

	// i = -1;
	// // printf("'");
	// // while (++i < csize)
	// // 	printf("%02x ", res[i]);
	// // printf("'\n");
	
	// iiii = open("res", O_CREAT | O_RDWR | O_TRUNC, 0755);
	// i = -1;
	// while (++i < reader2->size)
	// 	dprintf(iiii, "%c", res[i]);
	// free(res);

	// free(f_key);
	// free(cypher);

	// return (0);

	delete_binary_reader(reader);

	if (option & F_NOOUTPUT)
		return (0);

	if (elf_insert_section(elf_file, option) == -1)
	{
		delete_elf_file(elf_file);
		ft_error("An error occured while inserting the new section");
		return (1);
	}

	packer(elf_file);
	delete_elf_file(elf_file);
}
