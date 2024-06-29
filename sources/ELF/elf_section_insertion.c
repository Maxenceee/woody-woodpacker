/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf_section_insertion.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:30:38 by mgama             #+#    #+#             */
/*   Updated: 2024/06/29 17:27:10 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

int		efl_find_last_prog_header(t_elf_file *elf)
{
	int	index = 0;

	for (int i = 0; i < elf->e_phnum; i++)
	{
		if (elf->program_headers[i].p_type == PT_LOAD)
		{
			index = i;
		}
	}
	return (index);
}

int		efl_find_last_section_header(t_elf_file *elf, int progindex)
{
	int	index = 0;

	t_elf_program_header *prog = (t_elf_program_header *)elf->program_headers + progindex;
	for (int j = 1; j < elf->e_shnum; j++)
	{
		if (elf->section_tables[j].sh_offset >= prog->p_offset &&
			elf->section_tables[j].sh_offset + elf->section_tables[j].sh_size <=
			prog->p_offset + prog->p_filesz)
		{
			index = j;
		}
	}
	return (index);
}

int	create_new_elf_section(t_elf_file *elf, int last_load_prog, int last_section_in_prog)
{
	t_elf_section_table	*new_section_headers;
	elf->e_shnum += 1;

	size_t new_section_headers_size = sizeof(t_elf_section_table) * elf->e_shnum;
	elf->section_tables = ft_realloc(elf->section_tables, new_section_headers_size);
	if (!elf->section_tables)
		return (-1);

	
	
}

void	elf_insert_section(t_elf_file *elf)
{
	int progi = efl_find_last_prog_header(elf);
	printf("last PT_LOAD header: %d\n", progi);
	printf("last section in header: %d\n", efl_find_last_section_header(elf, progi));
}
