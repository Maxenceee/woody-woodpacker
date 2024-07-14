/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf_section_insertion.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 23:07:23 by mgama             #+#    #+#             */
/*   Updated: 2024/07/14 17:46:11 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

size_t calculate_padding(size_t size, size_t alignment) {
	size_t padding = (alignment - (size % alignment)) % alignment;
	return (padding);
}

size_t calculate_padded_size(size_t size, size_t alignment) {
	size_t padding = (alignment - (size % alignment)) % alignment;
	return (size + padding);
}

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
			elf->section_tables[j].sh_offset + elf->section_tables[j].sh_size <= prog->p_offset + prog->p_filesz)
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

	// printf("last_section_in_prog: %s\n", elf->section_tables[last_section_in_prog].sh_name);
	// printf("last_section_in_prog: %#lx\n", elf->section_tables[last_section_in_prog].sh_offset + elf->section_tables[last_section_in_prog].sh_size);

	uint64_t current_offset_padding = calculate_padding(elf->section_tables[last_section_in_prog].sh_offset + elf->section_tables[last_section_in_prog].sh_size, elf->section_tables[last_section_in_prog].sh_addralign);
	uint64_t current_offset = elf->section_tables[last_section_in_prog].sh_offset + elf->section_tables[last_section_in_prog].sh_size + current_offset_padding;
	uint64_t current_vaddr_padding = calculate_padding(elf->section_tables[last_section_in_prog].sh_address + elf->section_tables[last_section_in_prog].sh_size, elf->section_tables[last_section_in_prog].sh_addralign);
	uint64_t current_vaddr = elf->section_tables[last_section_in_prog].sh_address + elf->section_tables[last_section_in_prog].sh_size + current_vaddr_padding;
	
	new_section->sh_offset = current_offset;
	new_section->sh_address = current_vaddr;
	packer->new_section_size = current_offset_padding;
	// printf("new_section->sh_offset: %#lx, new_section->sh_address: %#lx\n", new_section->sh_offset, new_section->sh_address);
	// printf("prog p_memsz addr: %#lx\n", elf->program_headers[last_load_prog].p_offset + elf->program_headers[last_load_prog].p_memsz);
	// printf("packer->new_section_size: %#lx\n\n", packer->new_section_size);

	packer->loader_offset = new_section->sh_address;

	if ((new_section->data = prepare_payload(new_section, packer)) == NULL)
	{
		free(new_section);
		return (-1);
	}

	new_section->sh_size = calculate_padded_size(packer->payload_64_size, new_section->sh_addralign);
	
	packer->new_section_size += new_section->sh_size;
	// printf("packer->new_section_size: %#lx\n\n", packer->new_section_size);
	// printf("new elf->program_headers[last_load_prog].p_memsz: %#lx\n\n", elf->program_headers[last_load_prog].p_memsz + packer->new_section_size);

	size_t remaining_after_section_headers_data_size = sizeof(t_elf_section_table) * (elf->e_shnum - last_section_in_prog - 1 - 1);
	size_t remaining_after_section_headers_count = sizeof(char *) * (elf->e_shnum - last_section_in_prog - 1 - 1);

	memmove(elf->section_tables + last_section_in_prog + 2, elf->section_tables + last_section_in_prog + 1, remaining_after_section_headers_data_size);

	last_section_in_prog += 1;

	if (elf->e_shstrndx != 0)
	{
		if (elf->e_shstrndx >= last_section_in_prog) {
			elf->e_shstrndx += 1;
		}

		if (set_new_elf_section_string_table(elf, new_section) == -1)
		{
			free(new_section);
			return (-1);
		}
	}
	else
	{
		dprintf(2, "No section string table found\n");
	}

	ft_memcpy(&elf->section_tables[last_section_in_prog], new_section, sizeof(t_elf_section_table));

	for (int i = 0; i < elf->e_shnum; i++) {
		char *section_name = elf->section_tables[i].sh_name;
		if (strcmp(section_name, ".symtab") == 0) {
			elf->section_tables[i].sh_link += 1;
			elf->section_tables[i].sh_size += ft_strlen(elf->section_tables[i].sh_name) + 1;
		}
	}

	free(new_section);
	return (0);
}

void	update_program_header(t_elf_file *elf, t_packer *packer, int last_loadable, int last_loadable_section)
{
	// // Mettre à jour la taille du segment
	elf->program_headers[last_loadable].p_memsz += packer->new_section_size;
	elf->program_headers[last_loadable].p_filesz += packer->new_section_size;

	// Mettre à jour les flags pour inclure les permissions d'exécution et d'écriture
	elf->program_headers[last_loadable].p_flags |= PF_X | PF_W | PF_R;
}

void	update_section_addr(t_elf_file *elf, t_packer *packer, int last_loadable)
{
	for (int i = last_loadable; i < elf->e_shnum - 1; i++) {
		if (elf->section_tables[i].sh_type == SHT_NOBITS) {
			elf->section_tables[i + 1].sh_offset = elf->section_tables[i].sh_offset;
			continue;
		}
		uint64_t offset_padding = calculate_padded_size(
			elf->section_tables[i].sh_offset + elf->section_tables[i].sh_size, 
			elf->section_tables[i + 1].sh_addralign
		) - (elf->section_tables[i].sh_offset + elf->section_tables[i].sh_size);

		elf->section_tables[i + 1].sh_offset = elf->section_tables[i].sh_offset + elf->section_tables[i].sh_size + offset_padding;
		elf->section_tables[i + 1].sh_address = elf->section_tables[i].sh_address + elf->section_tables[i].sh_size + offset_padding;
	}

	int section_count = elf->e_shnum;
	elf->e_shoff = elf->section_tables[section_count - 1].sh_offset + elf->section_tables[section_count - 1].sh_size;
}

void	update_entry_point(t_elf_file *elf, t_packer *packer, int last_loadable)
{
	uint64_t last_entry_point = elf->e_entry;
	elf->e_entry = elf->section_tables[last_loadable].sh_address;
	// printf("last_entry_point: %#lx\n", last_entry_point);
	// printf("new_entry_point: %#lx\n", elf->e_entry);

	uint64_t jmp_instruction_address = elf->e_entry + packer->payload_64_size - WD_PAYLOAD_RETURN_ADDR;
	uint64_t next_instruction_address = jmp_instruction_address;
	// int32_t offset = (int32_t)(last_entry_point - next_instruction_address);
	int32_t offset = last_entry_point;
	// printf("offset: %d\n", offset);
	// printf("calc new_entry_point: %#lx\n", jmp_instruction_address + offset);

	ft_memcpy(elf->section_tables[last_loadable].data + packer->payload_64_size - WD_PAYLOAD_RETURN_ADDR, &offset, sizeof(offset));
}

int	elf_insert_section(t_elf_file *elf)
{
	t_packer	packer;
	packer.payload_64_size = WB_PAYLOAD_SIZE;
	packer.payload_64 = (uint8_t *)wd_playload_64;
	// packer.new_section_size = 0;
	
	int progi = efl_find_last_prog_header(elf);
	int sectioni = efl_find_last_section_header(elf, progi);
	if (create_new_elf_section(elf, &packer, progi, sectioni) == -1)
		return (-1);

	sectioni += 1;
	update_program_header(elf, &packer, progi, sectioni);
	update_section_addr(elf, &packer, sectioni);
	update_entry_point(elf, &packer, sectioni);
	return (0);
}
