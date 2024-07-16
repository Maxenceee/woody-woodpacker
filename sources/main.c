/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:07:36 by mbrement          #+#    #+#             */
/*   Updated: 2024/07/16 20:13:49 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

char *optarg = NULL; 
int optind = 1;
uint8_t key_aes[] = "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef";

static void	usage(void)
{
	(void)fprintf(stderr, "%s\n", "usage: woody_woodpacker [-h] [-s] [-d] [-k key] file");
	exit(64);
}

int ft_getopt(int argc, char * const argv[], const char *optstring)
{
	static int optpos = 1;

	if (optind >= argc || argv[optind][0] != '-') {
		return (-1);
	}

	if (argv[optind][0] == '-' && argv[optind][1] == '-') {
		optind++;
		return (-1);
	}

	if (optpos == 1 && strchr(optstring, argv[optind][1]) && strchr(optstring, argv[optind][1])[1] == ':') {
		if (argv[optind][2] != '\0') {
			optarg = &argv[optind][2];
			optind++;
			return (argv[optind - 1][1]);
		} else if (optind + 1 < argc) {
			optarg = argv[optind + 1];
			optind += 2;
			return (argv[optind - 2][1]);
		} else {
			optind++;
			return ('?');
		}
	}

	if (argv[optind][optpos] == '\0') {
		optind++;
		optpos = 1;
		return (ft_getopt(argc, argv, optstring));
	}

	char optchar = argv[optind][optpos];
	char *optdecl = strchr(optstring, optchar);

	if (optdecl == NULL) {
		optpos++;
		if (argv[optind][optpos] == '\0') {
			optind++;
			optpos = 1;
		}
		return ('?');
	}

	if (optdecl[1] == ':') {
		optind++;
		optpos = 1;
		return ('?');
	} else {
		optpos++;
		if (argv[optind][optpos] == '\0') {
			optind++;
			optpos = 1;
		}
		return (optchar);
	}
}

void	printbytes(uint8_t *bytes, size_t size)
{
	size_t i = 0;
	while (i < size)
	{
		printf("%02x ", bytes[i]);
		i++;
	}
	printf("\n");
}

int	main(int ac, char **av)
{
	char *target;
	int ch, option = 0;
	
	while ((ch = ft_getopt(ac, av, "k:hsdn")) != -1) {
		switch (ch) {
			case 'k':
				option |= F_KEY;
				ft_memmove(key_aes, optarg, 32);
				break;
			case 'h':
				option |= F_HEADER;
				break;
			case 's':
				option |= F_SECTION;
				break;
			case 'd':
				option |= F_DATA;
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
		printf("Error: Cannot get format for file %s\n", target);
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

	if (option & F_NOOUTPUT)
		return (0);

	packer(elf_file, reader);

	delete_binary_reader(reader);
	// delete_elf_file(elf_file);
}
