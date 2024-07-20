/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf_section_insertion.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 23:07:23 by mgama             #+#    #+#             */
/*   Updated: 2024/07/20 15:39:49 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"
#include <stdio.h>

size_t calculate_padding(size_t size, size_t alignment) {
	size_t padding = (alignment - (size % alignment)) % alignment;
	return (padding);
}

size_t calculate_padded_size(size_t size, size_t alignment) {
	size_t padding = (alignment - (size % alignment)) % alignment;
	return (size + padding);
}

int	has_section(t_elf_file *elf, const char *name)
{
	for (int i = 0; i < elf->e_shnum; i++) {
		if (elf->section_tables[i].sh_name && strcmp(elf->section_tables[i].sh_name, name) == 0) {
			return (1);
		}
	}
	return (0);
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

uint8_t	*prepare_payload(t_elf_section *new_section_headers, t_elf_section *text_section, t_packer *packer)
{
	(void)new_section_headers;

	uint8_t	*payload = (uint8_t *)malloc(packer->payload_64_size);
	if (!payload)
		return (NULL);

	ft_memcpy(payload, packer->payload_64, packer->payload_64_size);
	// Copy key inside payload
	ft_memcpy(payload + packer->payload_64_size - WD_PAYLOAD_OFF_KEY, key_aes, WD_AES_KEY_SIZE);

	// printf("WD_PAYLOAD_OFF_DATA_START: %#016x\n", text_section->sh_offset);
	// printf("WD_PAYLOAD_OFF_DATA_SIZE: %#016x\n", text_section->sh_size);
	// ft_memcpy(payload + packer->payload_64_size - WD_PAYLOAD_OFF_DATA_START, &text_section->sh_offset, sizeof(uint64_t));
	// ft_memcpy(payload + packer->payload_64_size - WD_PAYLOAD_OFF_DATA_SIZE, &text_section->sh_size, sizeof(uint64_t));
	return (payload);
}

int	set_new_elf_section_string_table(t_elf_file *elf, t_elf_section *new_section)
{
	char *section_name = malloc(sizeof(WB_SECTION_NAME) + 1);
	if (section_name == NULL) {
		return (-1);
	}
	ft_memcpy(section_name, WB_SECTION_NAME, sizeof(WB_SECTION_NAME));
	size_t section_name_len = sizeof(WB_SECTION_NAME) + 1;

	while (has_section(elf, section_name))
	{
		section_name = ft_strjoin(section_name, "-2");
		if (section_name == NULL) {
			return (-1);
		}
		section_name_len += 2;
	}

	int section_string_table_index = elf->e_shstrndx;
	int old_size = elf->section_tables[section_string_table_index].sh_size;

	size_t new_string_table_size = old_size + section_name_len;
	void *tmp = malloc(new_string_table_size);
	if (tmp == NULL)
	{
		printf("Bad readlloc in set_new_elf_section_string_table\n");
		free(section_name);
		return (-1);
	}
	ft_memcpy(tmp, elf->section_tables[section_string_table_index].data, old_size);
	free(elf->section_tables[section_string_table_index].data);
	elf->section_tables[section_string_table_index].data = tmp;

	ft_memmove(elf->section_tables[section_string_table_index].data + old_size, section_name, section_name_len);
	new_section->sh_name_offset = old_size;
	new_section->sh_name = section_name;
	elf->section_tables[section_string_table_index].sh_size = new_string_table_size;
	return (0);
}

int	create_new_elf_section(t_elf_file *elf, t_packer *packer, int last_load_prog, int last_section_in_prog)
{
	(void)last_load_prog;
	elf->e_shnum += 1;

	size_t new_section_headers_size = sizeof(t_elf_section) * elf->e_shnum;
	void *tmp = malloc(new_section_headers_size);
	if (tmp == NULL)
	{
		printf("Bad readlloc in create_new_elf_section\n");
		return (-1);
	}
	ft_memcpy(tmp, elf->section_tables, sizeof(t_elf_section) * (elf->e_shnum - 1));
	printf("%p\n", elf->section_tables);
	free(elf->section_tables);
	elf->section_tables = tmp;
	printf("%p\n", elf->section_tables);

	t_elf_section *new_section = ft_calloc(1, sizeof(t_elf_section));
	if (new_section == NULL)
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

	/* TODO: check if text_section is NULL*/
	t_elf_section *text_section = get_text_section(elf);
	if ((new_section->data = prepare_payload(new_section, text_section, packer)) == NULL)
	{
		free(new_section);
		return (-1);
	}

	new_section->sh_size = calculate_padded_size(packer->payload_64_size, new_section->sh_addralign);
	packer->new_section_size += new_section->sh_size;
	// printf("packer->new_section_size: %#lx\n\n", packer->new_section_size);
	// printf("new elf->program_headers[last_load_prog].p_memsz: %#lx\n\n", elf->program_headers[last_load_prog].p_memsz + packer->new_section_size);

	size_t remaining_after_section_headers_data_size = sizeof(t_elf_section) * (elf->e_shnum - last_section_in_prog - 1 - 1);

	ft_memmove(elf->section_tables + last_section_in_prog + 2, elf->section_tables + last_section_in_prog + 1, remaining_after_section_headers_data_size);

	last_section_in_prog += 1;
	ft_memset(&elf->section_tables[last_section_in_prog], 0, sizeof(t_elf_section));

	if (elf->e_shstrndx != 0)
	{
		if (elf->e_shstrndx >= last_section_in_prog) {
			elf->e_shstrndx += 1;
		}

		if (set_new_elf_section_string_table(elf, new_section) == -1)
		{
			if (new_section->data)
				free(new_section->data);
			free(new_section);
			return (-1);
		}
	}
	else
	{
		ft_error("No section string table found");
	}

	ft_memcpy(&elf->section_tables[last_section_in_prog], new_section, sizeof(t_elf_section));

	for (int i = 0; i < elf->e_shnum; i++) {
		if (strcmp(elf->section_tables[i].sh_name, ".symtab") == 0) {
			elf->section_tables[i].sh_link += 1;
		}
	}

	free(new_section);
	return (0);
}

void	update_program_header(t_elf_file *elf, t_packer *packer, int last_loadable, int last_loadable_section)
{
	(void)last_loadable_section;
	// // Mettre à jour la taille du segment
	elf->program_headers[last_loadable].p_memsz += packer->new_section_size;
	elf->program_headers[last_loadable].p_filesz += packer->new_section_size;

	// Mettre à jour les flags pour inclure les permissions d'exécution et d'écriture
	elf->program_headers[last_loadable].p_flags |= PF_X | PF_W | PF_R;
}

void	update_section_addr(t_elf_file *elf, t_packer *packer, int last_loadable)
{
	(void)packer;
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
	printf("last_entry_point: %#lx\n", last_entry_point);
	printf("new_entry_point: %#lx\n", elf->e_entry);

	uint64_t jmp_instruction_address = elf->e_entry + packer->payload_64_size - WD_PAYLOAD_RETURN_ADDR;
	uint64_t next_instruction_address = jmp_instruction_address + 4; // + 4 bytes to go to the address of the instruction after jump
	int32_t offset = (int32_t)(last_entry_point - next_instruction_address);
	printf("offset: %d => %#x\n", offset, offset);
	printf("calc new_entry_point: %#lx\n", jmp_instruction_address + offset);

	/**
	 * TODO:
	 * mettre a jour les offset pour pas tout casser
	 */
	ft_memcpy(elf->section_tables[last_loadable].data + packer->payload_64_size - WD_PAYLOAD_RETURN_ADDR, &offset, sizeof(offset));
}

void	update_symbols(t_elf_file *elf, t_packer *packer)
{
	int symstr_idx = 0;
	int symtab_idx = 0;

	for (uint16_t i = 0; i < elf->e_shnum; i++) {
		if (strcmp(elf->section_tables[i].sh_name, ".symtab") == 0 && elf->section_tables[i].sh_type == SHT_SYMTAB)
			symtab_idx = i;
		else if (strcmp(elf->section_tables[i].sh_name, ".strtab") == 0 && elf->section_tables[i].sh_type == SHT_STRTAB)
			symstr_idx = i;
	}
	if (symtab_idx == 0 || symstr_idx == 0)
	{
		ft_warning("Could not update symbol table");
		return ;
	}

	t_elf_sym sym;
	for (size_t j = 0; j * sizeof(t_elf_sym) < elf->section_tables[symtab_idx].sh_size; j++) {
		void *absoffset = elf->section_tables[symtab_idx].data + j * sizeof(t_elf_sym);
		memmove(&sym, absoffset, sizeof(sym));

		if (sym.st_name == 0)
			continue;

		if (strcmp((char *)(elf->section_tables[symstr_idx].data + sym.st_name), "_start") == 0)
		{
			sym.st_value = elf->e_entry;
			memmove(absoffset, &sym, sizeof(sym));
			break;
		}
	}
}

int	elf_insert_section(t_elf_file *elf, int opt)
{
	t_packer	packer;
	packer.payload_64_size = WB_PAYLOAD_SIZE;
	packer.payload_64 = (uint8_t *)wd_playload_64;
	packer.new_section_size = 0;
	
	int progi = efl_find_last_prog_header(elf);
	int sectioni = efl_find_last_section_header(elf, progi);
	if (create_new_elf_section(elf, &packer, progi, sectioni) == -1)
		return (-1);

	sectioni += 1;
	update_program_header(elf, &packer, progi, sectioni);
	update_section_addr(elf, &packer, sectioni);
	update_entry_point(elf, &packer, sectioni);

	if (opt & F_UDSYM)
		update_symbols(elf, &packer);
	return (0);
}
