/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:07:36 by mbrement          #+#    #+#             */
/*   Updated: 2024/07/18 22:48:42 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/utils.h"
#include "woody.h"

uint8_t key_aes[WD_AES_KEY_SIZE];

static void	usage(void)
{
	(void)fprintf(stderr, "%s\n", "usage: woody_woodpacker <option(s)> file");
	(void)fprintf(stderr, "  %s\n", "Options are:");
	(void)fprintf(stderr, "  %-20s %s\n", "-h, --file-header", "Display the ELF file header");
	(void)fprintf(stderr, "  %-20s %s\n", "-l, --segments", "Display the program headers");
	(void)fprintf(stderr, "  %-20s %s\n", "-S, --sections", "Display the sections' header");
	(void)fprintf(stderr, "  %-20s %s\n", "-s, --symbols", "Display the symbol table");
	(void)fprintf(stderr, "  %-20s %s\n", "-d, --data", "Display the section data");
	(void)fprintf(stderr, "  %-20s %s\n", "-g, --update-syms", "Update debug symbols");
	(void)fprintf(stderr, "  %-20s %s\n", "-k, --key=<key-val|@file_path>", "Use custom encrypt key (64 bytes)");
	exit(64);
}

int	main(int ac, char **av)
{
	char *target;
	int ch, option = 0;

	struct optparse_long longopts[] = {
        {"file-header", 'h', OPTPARSE_NONE},
        {"segments", 'l', OPTPARSE_NONE},
        {"sections", 'S', OPTPARSE_NONE},
        {"symbols", 's', OPTPARSE_NONE},
        {"data", 'd', OPTPARSE_NONE},
        {"update-syms", 'g', OPTPARSE_NONE},
        {"key", 'k', OPTPARSE_REQUIRED},
		{"no-output", 'n', OPTPARSE_NONE},
        {0}
    };
	struct optparse options;

    optparse_init(&options, av);
	while ((ch = optparse_long(&options, longopts, NULL)) != -1) {
		switch (ch) {
			case 'k':
				option |= F_KEY;
				if (options.optarg[0] == '@')
				{
					int fd = open(options.optarg + 1, O_RDONLY);
					if (fd == -1)
					{
						ft_error_msg("Cannot open file", options.optarg + 1);
						return (1);
					}
					if (read(fd, key_aes, WD_AES_KEY_SIZE) != WD_AES_KEY_SIZE)
					{
						ft_error_msg("Cannot read key from file", options.optarg + 1);
						return (1);
					}
					close(fd);
					break;
				}
				if (ft_strlen(options.optarg) != WD_AES_KEY_SIZE)
					ft_warning("Key should be 64 bytes long");
				ft_memmove(key_aes, options.optarg, WD_AES_KEY_SIZE);
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

	if (ac - options.optind != 1)
		usage();
	target = av[options.optind];

	int fd = open(target, O_RDONLY);
	if (fd == -1)
	{
		printf("Error: Cannot open file %s\n", target);
		return (1);
	}

	if (0 == (option & F_KEY))
	{
		gen_aes_key(key_aes, WD_AES_KEY_SIZE);
	}

	/**
	 * Create new reader
	 */
	t_binary_reader *reader = new_binary_reader(fd);
	if (!reader)
	{
		close(fd);
		printf("Error: Cannot read file %s\n", target);
		return (1);
	}
	close(fd);

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
	// printf("Key: %s\n", key_aes);
	printf("Key: 0x");
	for (size_t i = 0; i < WD_AES_KEY_SIZE; i++)
		printf("%02x", key_aes[i]);
	printf("\n");
	printf("================================================\n");

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
