/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:07:36 by mbrement          #+#    #+#             */
/*   Updated: 2024/07/24 18:14:29 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/utils.h"
#include "woody.h"

uint8_t key_aes[WD_AES_KEY_SIZE];

static void	usage(void)
{
	(void)fprintf(stderr, "%s\n", "usage: woody_woodpacker <option(s)> file");
	(void)fprintf(stderr, "  %s\n", "Options are:");
	(void)fprintf(stderr, "  %s, %-20s %s\n", "-h", "--file-header", "Display the ELF file header");
	(void)fprintf(stderr, "  %s, %-20s %s\n", "-l", "--segments", "Display the program headers");
	(void)fprintf(stderr, "  %s, %-20s %s\n", "-S", "--sections", "Display the sections' header");
	(void)fprintf(stderr, "  %s, %-20s %s\n", "-s", "--symbols", "Display the symbol table");
	(void)fprintf(stderr, "  %s, %-20s %s\n", "-d", "--data", "Display the section data");
	(void)fprintf(stderr, "  %s, %-20s %s\n", "-g", "--update-syms", "Update debug symbols");
	(void)fprintf(stderr, "  %s, %-20s %s\n", "-k", "--key=<key-val|@file_path>", "Use custom encrypt key (16 bytes)");
	(void)fprintf(stderr, "  %s, %-20s %s\n", "-v", "--verbose", "Verbose mode");
	(void)fprintf(stderr, "  %s, %-20s %s\n", "-V", "--version", "Print version");
	(void)fprintf(stderr, "  Don't pack itself !\n");
	exit(64);
}

void	header(void)
{
	printf(HEADER"\n              .\n           ,'/ \\`.\n          |\\/___\\/|\n          \\'\\   /`/\n           `.\\ /,'\n              |\n              |\n             |=|\n        /\\  ,|=|.  /\\\n    ,'`.  \\/ |=| \\/  ,'`.\n  ,'    `.|\\ `-' /|,'    `.\n,'   .-._ \\ `---' / _,-.   `.\n   ,'    `-`-._,-'-'    `.\n  '                       `\n"RESET);
	printf("%*s%sWoodyWoodpacker%s\n\n", 8, "", HACKER, RESET);
}

int	main(int ac, char **av)
{
	char *target;
	int ch, option = 0;
	int key_size = WD_AES_KEY_SIZE;

	struct getopt_list_s optlist[] = {
        {"file-header", 'h', OPTPARSE_NONE},
        {"segments", 'l', OPTPARSE_NONE},
        {"sections", 'S', OPTPARSE_NONE},
        {"symbols", 's', OPTPARSE_NONE},
        {"data", 'd', OPTPARSE_NONE},
        {"update-syms", 'g', OPTPARSE_NONE},
        {"key", 'k', OPTPARSE_REQUIRED},
        {"verbose", 'v', OPTPARSE_NONE},
        {"version", 'V', OPTPARSE_NONE},
		{"no-pack", 'n', OPTPARSE_NONE},
        {0}
    };
	struct getopt_s options;

	header();

    ft_getopt_init(&options, av);
	while ((ch = ft_getopt(&options, optlist, NULL)) != -1) {
		switch (ch) {
			case 'k':
				option |= F_KEY;
				if (options.optarg[0] == '@')
				{
					int fd = open(options.optarg + 1, O_RDONLY);
					if (fd == -1)
					{
						ft_error_msg("Cannot open key file", options.optarg + 1);
						return (1);
					}
					/**
					 * Check file content size macthes WD_AES_KEY_SIZE:
					 * - If the number of bytes read is less than WD_AES_KEY_SIZE
					 * - Seek to the end and check if the offset is greater than WD_AES_KEY_SIZE
					 */
					if ((key_size = read(fd, key_aes, WD_AES_KEY_SIZE)) != WD_AES_KEY_SIZE || lseek(fd, 0, SEEK_END) != WD_AES_KEY_SIZE)
					{
						if (key_size != -1)
						{
							ft_warning("Key file should contain 16 bytes, key will be risized");
							break;	
						}
						ft_error_msg("Cannot read key from file", options.optarg + 1);
						return (1);
					}
					(void)close(fd);
					break;
				}
				if ((key_size = ft_strlen(options.optarg)) != WD_AES_KEY_SIZE)
					ft_warning("Key should be 16 bytes long, key will be risized");
				ft_memmove(key_aes, options.optarg, ft_min(key_size, WD_AES_KEY_SIZE));
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
			case 'v':
				verbose_mode = VERBOSE_ON;
				break;
			case 'V':
				printf(B_PINK"Woody Woodpacker version %s%s%s by %s%s%s\n"RESET, CYAN, WD_VERSION, B_PINK, CYAN, WD_AUTHOR, RESET);
				exit(0);
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

	if (is_same_file(av[0], target))
	{
		ft_error("Cannot pack itself ! Nice try ;)");
		return (1);
	}

	ft_verbose("\n%s<== Verbose mode activated ==>%s\n\n", B_RED, RESET);

	ft_verbose("Target file: `%s%s%s`\n", B_CYAN, target, RESET);

	int fd = open(target, O_RDONLY);
	if (fd == -1)
	{
		ft_error_msg("Cannot open file", target);
		return (1);
	}

	if (0 == (option & F_KEY))
	{
		ft_verbose("\nNo key provided, generating one\n");
		ft_verbose("Generating AES key...\n");
		gen_aes_key(key_aes, WD_AES_KEY_SIZE);
	}

	printf("\nAES key: %s0x", B_PINK);
	for (size_t i = 0; i < WD_AES_KEY_SIZE; i++)
		printf("%02x", key_aes[i]);
	printf(RESET"\n");
	printf("AES key (ASCII): %s%s%s\n", B_CYAN, key_aes, RESET);

	/**
	 * Create new reader
	 */
	t_binary_reader *reader = new_binary_reader(fd);
	if (!reader)
	{
		close(fd);
		ft_error_msg("Cannot read file", target);
		return (1);
	}
	close(fd);

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

	delete_binary_reader(reader);

	if (option & F_NOOUTPUT)
	{
		ft_verbose("\nNo packaging option, skipping the packer\n");
		return (0);
	}

	if (elf_insert_section(elf_file, option) == -1)
	{
		delete_elf_file(elf_file);
		ft_error("An error occured while inserting the new section");
		return (1);
	}
	
	packer(elf_file);
	ft_verbose(B_GREEN"\nFile `%s%s%s` successfully packed in %s%s%s !\n"RESET, B_CYAN, target, B_GREEN, B_CYAN, WD_OUTPUT_FILE, B_GREEN);
	delete_elf_file(elf_file);
}
