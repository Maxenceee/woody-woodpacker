/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   packer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:59:30 by mgama             #+#    #+#             */
/*   Updated: 2024/07/14 14:47:40 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

size_t offset = 0;

int	write_to_file(int fd, void *data, size_t size) {
	ssize_t written = write(fd, data, size);
	if (written == -1) {
		return (-1);
	}
	offset += written;
	return (0);
}

void add_zero_padding(int fd, size_t end_offset) {
    char c = 0;

    while(offset < end_offset) {
        write_to_file(fd, &c, sizeof(c));
    }
}

int	packer(t_elf_file *elf, t_binary_reader *reader)
{
	if (elf_insert_section(elf) == -1)
	{
		return (ft_error("An error occured while inserting the new section"));
	}

	int fd = open("woody", O_CREAT | O_WRONLY | O_TRUNC, 0755);
	if (fd == -1)
		return (ft_error("Could not open file."), 1);

	size_t elf_header_size = sizeof(t_elf_file) - sizeof(char *) - sizeof(t_elf_program_header *) - sizeof(t_elf_section_table *);
	size_t elf_section_header_size = sizeof(t_elf_section_table) - sizeof(char *) - sizeof(uint8_t *);

	write_to_file(fd, elf, elf_header_size);
	add_zero_padding(fd, elf->e_phoff);

	for (int i = 0; i < elf->e_phnum; i++) {
		write_to_file(fd, &elf->program_headers[i], sizeof(t_elf_program_header));
	}

	for (int i = 0; i < elf->e_shnum; i++) {
		if (elf->section_tables[i].sh_type != SHT_NOBITS)
		{
			add_zero_padding(fd, elf->section_tables[i].sh_offset);
			write_to_file(fd, elf->section_tables[i].data, elf->section_tables[i].sh_size);
		}
	}

	add_zero_padding(fd, elf->e_shoff);

	for (int i = 0; i < elf->e_shnum; i++) {
		write_to_file(fd, &elf->section_tables[i], elf_section_header_size);
	}

	close(fd);
	return (0);
}
