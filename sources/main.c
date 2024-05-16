/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:07:36 by mbrement          #+#    #+#             */
/*   Updated: 2024/05/16 10:45:22 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AES/aes.h"
#include "woody.h"
#include <fcntl.h>
#include <stdint.h>
#include <string.h>

char *optarg = NULL; 
int optind = 1;

static void	usage(void)
{
	(void)fprintf(stderr, "%s\n", "usage: woody_woodpacker [-e key] [-d key] file");
	exit(64);
}

int ft_getopt(int argc, char * const argv[], const char *optstring) {
	char *optchar;

	if (optind >= argc || argv[optind][0] != '-') {
		return -1; // Pas plus d'options ou ce n'est pas une option
	}

	optchar = strchr(optstring, argv[optind][1]);
	if (optchar == NULL) {
		fprintf(stderr, "Unknown option: %c\n", argv[optind][1]);
		optind++;
		return '?';
	}

	if (optchar[1] == ':') { // L'option nécessite un argument
		if (optind + 1 < argc) {
			optarg = argv[optind + 1];
			optind += 2;
			return optchar[0];
		} else {
			fprintf(stderr, "Option requires an argument.\n");
			optind++;
			return '?';
		}
	} else { // L'option ne nécessite pas d'argument
		optind++;
		return optchar[0];
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
	char key[] = "0123456789abcdef0123456789abcdef";
	
	while ((ch = ft_getopt(ac, av, "e:d:k:h")) != -1) {
		switch (ch) {
			case 'k':
				option |= F_KEY;
				memmove(key, optarg, 32);
				break;
			case 'h':
				option |= F_HEADER;
				break;
			case 'e':
				option |= F_ENCRYPT;
				break;
			case 'd':
				option |= F_DECRYPT;
				break;
			default:
				usage();
		}
	}

	if (ac - optind != 1)
		usage();
	target = av[optind];

	printf("Target: %s\n", target);

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
		print_elf_file(elf_file);
	}

	/**
	 * 
	 * olalaaaaaa ke sai pa bo !!!!!!!!!!
	 *
	 */
	
	int ffd = open("woody_encrypted", O_CREAT | O_RDWR | O_TRUNC, 0755);

	uint8_t input[16];
	reader->seek(reader, 0x0);
	char key2[33];
	memmove(key2, key, 32);
	while (reader->get_bytes(reader, input, 16))
	{
		char *res = *AES_encrypt(input, key2);
		write(ffd, res, 16);
	}
	printf("key -> %s\n", key);
	int ffdd = open("woody_decrypted", O_CREAT | O_WRONLY | O_TRUNC, 0755);

	reader = new_binary_reader(ffd);
	reader->seek(reader, 0x0);
	while (reader->get_bytes(reader, input, 16))
	{
		char *res = *AES_decrypt(input, key);
		write(ffdd, res, 16);
	}

	close(ffd);
	close(ffdd);
	
	return (0);

	/**
	 * 
	 * oufff c'est enfin fini !!!
	 * 
	 */

	// printf("=================+++++=====\n%#x %#lx\n", payload_64, payload_size_64);

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
