/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:07:36 by mbrement          #+#    #+#             */
/*   Updated: 2024/07/02 19:24:37 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

char *optarg = NULL; 
int optind = 1;

static void	usage(void)
{
	(void)fprintf(stderr, "%s\n", "usage: woody_woodpacker [-e key] [-d key] file");
	exit(64);
}

int ft_getopt(int argc, char * const argv[], const char *optstring) {
	char *optchar;

	optarg = NULL;
	if (optind >= argc || argv[optind][0] != '-') {
		return -1; // Pas plus d'options ou ce n'est pas une option
	}

	optchar = strchr(optstring, argv[optind][1]);
	if (optchar == NULL) {
		optind++;
		return -1;
	}

	if (optchar[1] == ':') { // L'option nécessite un argument
		if (optind + 1 < argc) {
			optarg = argv[optind + 1];
			optind += 2;
			return optchar[0];
		} else {
			optind++;
			return -1;
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
	static char key[] = "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef";
	
	/**
	 * TODO:
	 * rm the following line and add the option
	 */
	option |= F_DATA;
	
	while ((ch = ft_getopt(ac, av, "e:d:k:hs")) != -1) {
		switch (ch) {
			case 'k':
				option |= F_KEY;
				memmove(key, optarg, 32);
				break;
			case 'h':
				option |= F_HEADER;
				break;
			case 's':
				option |= F_SECTION;
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


	// /**
	//  * test writer
	//  * 
	//  */


	// uint8_t * tt = malloc(200);
	// t_binary_writer *writer = new_binary_writer(tt, 200);
	
	// writer->set_uint8(writer, 0x01);
	// writer->set_padding(writer, 15);
	// writer->set_uint16(writer, 0x0203);
	// writer->set_padding(writer, 14);
	// writer->set_uint32(writer, 0x04050607);
	// writer->set_padding(writer, 12);
	// writer->set_uint64(writer, 0x08090a0b0c0d0e0f);
	// writer->set_padding(writer, 8);
	// writer->set_string(writer, "Hello World");
	// writer->set_padding(writer, 5);
	// uint8_t d[8] = {0x10, 0x09, 0x08, 0x07, 0x06, 0x05,0x04, 0x03};
	// writer->set_bytes(writer, d, 8);
	// writer->set_padding(writer, 8);
	// writer->set_endian(writer, WRITER_BIG_ENDIAN);
	// writer->set_string(writer, "Hello World");
	// writer->set_padding(writer, 5);
	// writer->set_bytes(writer, d, 8);
	// writer->set_padding(writer, 8);
	// writer->set_uint8(writer, 0x01);
	// writer->set_padding(writer, 15);
	// writer->set_uint16(writer, 0x0203);
	// writer->set_padding(writer, 14);
	// writer->set_uint32(writer, 0x04050607);
	// writer->set_padding(writer, 12);
	// writer->set_uint64(writer, 0x08090a0b0c0d0e0f);
	// writer->set_padding(writer, 8);
	// writer->write_file(writer, "test.out");

	// return (0);

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

	elf_insert_section(elf_file);

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

	// // i = -1;
	// // // printf("'");
	// // // while (++i < csize)
	// // // 	printf("%02x ", res[i]);
	// // // printf("'\n");
	
	// iiii = open("res", O_CREAT | O_RDWR | O_TRUNC, 0755);
	// i = -1;
	// while (++i < reader2->size)
	// 	dprintf(iiii, "%c", res[i]);
	// free(res);

	// free(f_key);
	// free(cypher);

	// return (0);

	/**
	 * 
	 * olalaaaaaa ke sai pa bo !!!!!!!!!!
	 *
	 */
	
	// int ffd = open("woody_encrypted", O_CREAT | O_RDWR | O_TRUNC, 0755);

	// uint8_t input[16];
	// reader->seek(reader, 0x0);
	// char key2[33];
	// memmove(key2, key, 32);
	// while (reader->get_bytes(reader, input, 16))
	// {
	// 	char *res = *AES_encrypt(input, key2);
	// 	write(ffd, res, 16);
	// }
	// printf("key -> %s\n", key);
	// int ffdd = open("woody_decrypted", O_CREAT | O_WRONLY | O_TRUNC, 0755);

	// reader = new_binary_reader(ffd);
	// reader->seek(reader, 0x0);
	// while (reader->get_bytes(reader, input, 16))
	// {
	// 	char *res = *AES_decrypt(input, key);
	// 	write(ffdd, res, 16);
	// }

	// close(ffd);
	// close(ffdd);
	
	// return (0);

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
