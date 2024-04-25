/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   packer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:59:30 by mgama             #+#    #+#             */
/*   Updated: 2024/04/25 17:44:11 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

static int	strip_sections(t_elf_file *old_elf_file, t_elf_file *new_elf_file, t_binary_reader *reader)
{
	new_elf_file->section_tables = NULL;
	int j = 0;
	for (int i = 0; i < old_elf_file->e_shnum; i++)
	{
		if (old_elf_file->section_tables[i].sh_type != 0x7) // NOTE
		{
			new_elf_file->section_tables = ft_realloc(new_elf_file->section_tables, sizeof(t_elf_section_table) * (i + 1));
			if (!new_elf_file->section_tables)
				return (ft_error(WD_PREFIX"Could not allocate memory.\n"), 1);
			new_elf_file->section_tables[j++] = old_elf_file->section_tables[i];
		}
	}
	new_elf_file->e_shnum = j;
	return (0);
}

static int strip_program_headers(t_elf_file *old_elf_file, t_elf_file *new_elf_file, t_binary_reader *reader)
{
	new_elf_file->program_headers = NULL;
	int j = 0;
	
	for (int i = 0; i < old_elf_file->e_phnum; i++)
	{
		// Vérifie si le segment contient des sections
		int has_sections = 0;
		for (int k = 0; k < old_elf_file->e_shnum; k++)
		{
			// if (new_elf_file->section_tables[k].sh_type == 0x0) continue;

			if (new_elf_file->section_tables[k].sh_address >= old_elf_file->program_headers[i].p_vaddr &&
				new_elf_file->section_tables[k].sh_address + new_elf_file->section_tables[k].sh_size <=
					old_elf_file->program_headers[i].p_vaddr + old_elf_file->program_headers[i].p_memsz)
			{
				has_sections = 1;
				break;
			}
		}
		
		// Si le segment ne contient pas de sections, ne l'ajoute pas aux nouveaux en-têtes de programme
		if (has_sections)
		{
			new_elf_file->program_headers = ft_realloc(new_elf_file->program_headers, sizeof(t_elf_program_header) * (j + 1));
			if (!new_elf_file->program_headers)
				return (ft_error(WD_PREFIX "Could not allocate memory.\n"), 1);
			new_elf_file->program_headers[j++] = old_elf_file->program_headers[i];
		}
	}
	
	new_elf_file->e_phnum = j;
	return (0);
}

int	packer(t_elf_file *old_elf_file, t_elf_file *new_elf_file, t_binary_reader *reader)
{
	int fd = open("woody", O_CREAT | O_WRONLY | O_TRUNC, 0755);
	if (fd == -1)
		return (ft_error(WD_PREFIX"Could not open file.\n"), 1);

	uint32_t magic = 0x464C457F;
	// write(fd, &magic, 4);
	// write(fd, &new_elf_file->e_ident_class, 1);
	// write(fd, &new_elf_file->e_ident_data, 1);
	// write(fd, &new_elf_file->e_ident_version, 1);
	// write(fd, &new_elf_file->e_ident_osabi, 1);
	// write(fd, &new_elf_file->e_ident_abi_version, 1);
	// write(fd, "\0\0\0\0\0\0\0", 7);
	// write(fd, &new_elf_file->e_type, 2);
	// write(fd, &new_elf_file->e_machine, 2);
	// write(fd, &new_elf_file->e_version, 4);
	// write(fd, "\0\0\0\0\0\0\0\0", new_elf_file->e_ident_class == WD_32BITS ? 4 : 8); // entry
	// write(fd, "\0\0\0\0\0\0\0\0", new_elf_file->e_ident_class == WD_32BITS ? 4 : 8); // phoff
	// write(fd, "\0\0\0\0\0\0\0\0", new_elf_file->e_ident_class == WD_32BITS ? 4 : 8); // shoff
	// write(fd, &new_elf_file->e_flags, 4);
	// write(fd, &new_elf_file->e_ehsize, 2);
	// write(fd, &new_elf_file->e_phentsize, 2);
	// write(fd, &new_elf_file->e_phnum, 2);
	// write(fd, &new_elf_file->e_shentsize, 2);
	// write(fd, "\0\0", 2);
	// write(fd, "\0\0", 2);

	if (strip_sections(old_elf_file, new_elf_file, reader))
	{
		close(fd);
		return (1);
	}

	if (strip_program_headers(old_elf_file, new_elf_file, reader))
	{
		close(fd);
		return (1);
	}

	print_elf_file(new_elf_file);

	close(fd);
	return (0);
}
