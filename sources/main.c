/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:07:36 by mbrement          #+#    #+#             */
/*   Updated: 2024/05/15 14:40:42 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AES/aes.h"
#include "woody.h"
#include <fcntl.h>
#include <stdint.h>

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

int	main(int ac, char **av)
{
	char *target;
	int ch;
	while ((ch = ft_getopt(ac, av, "e:d:")) != -1) {
        switch (ch) {
            case 'e':
				printf("Option e: %s\n", optarg);
                break;
            case 'd':
                printf("Option d: %s\n", optarg);
                break;
			default:
				usage();
        }
    }

	if (ac - optind != 1)
		usage();
	target = av[optind];

	printf("Target: %s\n", target);

	if (ac > 2 && av[1][0] == '-' && av[1][1] == 'e')
		(void)AES_file(av[2], av[3], 1);
	else if (ac > 2 && av[1][0] == '-' && av[1][1] == 'd')
		(void)AES_file(av[2], av[3], 2);
	else if (ac != 2)
	{
		printf("Usage: %s <file>\n", av[0]);
		return (1);
	}

	return (0);

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

	printf("=================+++++=====\n%#x %#llx\n", payload_64, payload_size_64);

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
