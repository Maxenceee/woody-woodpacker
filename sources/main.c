#include <stdio.h>
#include <fcntl.h>
#include "reader/binary_reader.h"

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

	// Skip the first byte of the file
	reader->get_uint8(reader);

	// Get the file type reading 3 bytes as a string
	char *filetype = reader->get_string(reader, 3);
	printf("File type: %s\n", filetype);
}
