/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   packer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:59:30 by mgama             #+#    #+#             */
/*   Updated: 2024/07/12 21:46:51 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

// static int	strip_sections(t_elf_file *old_elf_file, t_elf_file *new_elf_file, t_binary_reader *reader)
// {
// 	new_elf_file->section_tables = NULL;
// 	int j = 0;
// 	for (int i = 0; i < old_elf_file->e_shnum; i++)
// 	{
// 		if (old_elf_file->section_tables[i].sh_type == 0x1) // PROGBITS
// 		{
// 			new_elf_file->section_tables = ft_realloc(new_elf_file->section_tables, sizeof(t_elf_section_table) * (i + 1));
// 			if (!new_elf_file->section_tables)
// 				return (ft_error(WD_PREFIX"Could not allocate memory.\n"), 1);
// 			new_elf_file->section_tables[j++] = old_elf_file->section_tables[i];
// 		}
// 	}
// 	new_elf_file->e_shnum = j;
// 	return (0);
// }

// static int strip_program_headers(t_elf_file *old_elf_file, t_elf_file *new_elf_file, t_binary_reader *reader)
// {
// 	new_elf_file->program_headers = NULL;
// 	int j = 0;
	
// 	for (int i = 0; i < old_elf_file->e_phnum; i++)
// 	{
// 		// Vérifie si le segment contient des sections
// 		int has_sections = 0;
// 		for (int k = 0; k < old_elf_file->e_shnum; k++)
// 		{
// 			// if (new_elf_file->section_tables[k].sh_type == 0x0) continue;

// 			// if (new_elf_file->section_tables[k].sh_address >= old_elf_file->program_headers[i].p_vaddr &&
// 			if (new_elf_file->section_tables[k].sh_address > old_elf_file->program_headers[i].p_vaddr &&
// 				new_elf_file->section_tables[k].sh_address + new_elf_file->section_tables[k].sh_size <=
// 					old_elf_file->program_headers[i].p_vaddr + old_elf_file->program_headers[i].p_memsz)
// 			{
// 				has_sections = 1;
// 				break;
// 			}
// 		}
		
// 		// Si le segment ne contient pas de sections, ne l'ajoute pas aux nouveaux en-têtes de programme
// 		if (has_sections)
// 		{
// 			new_elf_file->program_headers = ft_realloc(new_elf_file->program_headers, sizeof(t_elf_program_header) * (j + 1));
// 			if (!new_elf_file->program_headers)
// 				return (ft_error(WD_PREFIX "Could not allocate memory.\n"), 1);
// 			new_elf_file->program_headers[j++] = old_elf_file->program_headers[i];
// 		}
// 	}
	
// 	new_elf_file->e_phnum = j;
// 	return (0);
// }

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
		dprintf(2, "An error occured while inserting the new section\n");
	}

	int fd = open("woody", O_CREAT | O_WRONLY | O_TRUNC, 0755);
	if (fd == -1)
		return (ft_error(WD_PREFIX"Could not open file.\n"), 1);

	size_t elf_header_size = sizeof(t_elf_file) - sizeof(char *) - sizeof(t_elf_program_header *) - sizeof(t_elf_section_table *);
	size_t elf_section_header_size = sizeof(t_elf_section_table) - sizeof(char *) - sizeof(uint8_t *);

	printf("elf_header_size: %zu\n", elf_header_size);
	printf("elf_section_header_size: %zu\n", elf_section_header_size);

	write_to_file(fd, elf, elf_header_size);
	add_zero_padding(fd, elf->e_phoff);

	for (int i = 0; i < elf->e_phnum; i++) {
		write_to_file(fd, &elf->program_headers[i], sizeof(t_elf_program_header));
	}

	// Write the section headers (excluding pointers)
	for (int i = 0; i < elf->e_shnum; i++) {
		if (elf->section_tables[i].sh_type != SHT_NOBITS)
		{
			add_zero_padding(fd, elf->section_tables[i].sh_offset);
			write_to_file(fd, elf->section_tables[i].data, elf->section_tables[i].sh_size);
		}
	}

	add_zero_padding(fd, elf->e_shoff);

	// Write the section data
	for (int i = 0; i < elf->e_shnum; i++) {
		write_to_file(fd, &elf->section_tables[i], elf_section_header_size);
	}

	print_elf_file(elf, PELF_ALL | PELF_DATA);

	close(fd);
	return (0);
}
