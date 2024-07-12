/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf_section_insertion.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:30:38 by mgama             #+#    #+#             */
/*   Updated: 2024/07/12 18:27:22 by mgama            ###   ########.fr       */
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

uint8_t	*prepare_payload(t_elf_section_table *new_section_headers, t_packer *packer)
{
	uint8_t	*payload = (uint8_t *)malloc(packer->payload_64_size);
	if (!payload)
		return (NULL);

	ft_memcpy(payload, packer->payload_64, packer->payload_64_size);
	ft_memcpy(payload + packer->payload_64_size - WD_PAYLOAD_OFF_KEY, key_aes, WD_AES_KEY_SIZE);
	return (payload);
}

int	set_new_elf_section_string_table(t_elf_file *elf, t_elf_section_table *new_section)
{
	if (elf->e_shstrndx == -1) {
		dprintf(2, "No section string table found\n");
		return (0);
	}
	char *section_name = WB_SECTION_NAME;
	size_t section_name_len = ft_strlen(section_name);

	int section_string_table_index = elf->e_shstrndx;
	int old_size = elf->section_tables[section_string_table_index].sh_size;

	size_t new_string_table_size = elf->section_tables[section_string_table_index].sh_size + section_name_len + 1;
	elf->section_tables[section_string_table_index].data = ft_realloc(elf->section_tables[section_string_table_index].data, new_string_table_size);
	if (elf->section_tables[section_string_table_index].data == NULL) {
		return (-1);
	}

	ft_memcpy(elf->section_tables[section_string_table_index].data + old_size, section_name, section_name_len + 1);
	new_section->sh_name_offset = old_size;
	new_section->sh_name = WB_SECTION_NAME;
	elf->section_tables[section_string_table_index].sh_size = new_string_table_size;
	return (0);
}

int	create_new_elf_section(t_elf_file *elf, t_packer *packer, int last_load_prog, int last_section_in_prog)
{
	t_elf_section_table	*new_section_headers;
	elf->e_shnum += 1;

	size_t new_section_headers_size = sizeof(t_elf_section_table) * elf->e_shnum;
	elf->section_tables = ft_realloc(elf->section_tables, new_section_headers_size);
	if (!elf->section_tables)
		return (-1);

	t_elf_section_table *new_section = ft_calloc(1, sizeof(t_elf_section_table));
	if (!new_section)
		return (-1);

	new_section->sh_type = SHT_PROGBITS;
	new_section->sh_flags = SHF_EXECINSTR | SHF_ALLOC;
    new_section->sh_addralign = 16;

	new_section->sh_offset = elf->program_headers[last_load_prog].p_offset + elf->program_headers[last_load_prog].p_memsz;
	new_section->sh_address = elf->program_headers[last_load_prog].p_vaddr + elf->program_headers[last_load_prog].p_memsz;
	
	new_section->sh_size = sizeof(wd_playload_64);
	packer->loader_offset = new_section->sh_address;

	if ((new_section->data = prepare_payload(new_section, packer)) == NULL)
	{
		free(new_section);
		return (-1);
	}

	size_t remaining_after_section_headers_data_size = sizeof(t_elf_section_table) * (elf->e_shnum - last_section_in_prog - 1 - 1);
    size_t remaining_after_section_headers_count = sizeof(char *) * (elf->e_shnum - last_section_in_prog - 1 - 1);

	memmove(elf->section_tables + last_section_in_prog + 2, elf->section_tables + last_section_in_prog + 1, remaining_after_section_headers_data_size);

	last_section_in_prog += 1;

	if (elf->e_shstrndx >= last_section_in_prog) {
		elf->e_shstrndx += 1;
	}

	if (set_new_elf_section_string_table(elf, new_section) == -1)
	{
		free(new_section);
		return (-1);
	}

	ft_memcpy(&elf->section_tables[last_section_in_prog], new_section, sizeof(t_elf_section_table));

	print_elf_file(elf, PELF_ALL | PELF_DATA);

	free(new_section->data);
	free(new_section);
	return (0);
}

int	elf_insert_section(t_elf_file *elf)
{
	t_packer	packer;
	packer.payload_64_size = WB_PAYLOAD_SIZE;
	packer.payload_64 = (uint8_t *)wd_playload_64;
	
	int progi = efl_find_last_prog_header(elf);
	int sectioni = efl_find_last_section_header(elf, progi);
	return (create_new_elf_section(elf, &packer, progi, sectioni));
}
