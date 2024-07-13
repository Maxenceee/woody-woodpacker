/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf_section_insertion.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:30:38 by mgama             #+#    #+#             */
/*   Updated: 2024/07/13 17:21:47 by mgama            ###   ########.fr       */
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
	// Calculer l'alignement de l'offset et la taille de fin
    uint64_t offset_padding = new_section_headers->sh_offset % 16;
    uint64_t end_padding = (offset_padding + packer->payload_64_size) % 16;
    
    printf("payload offset_padding: %lu\n", offset_padding);
    printf("payload size: %lu\n", packer->payload_64_size);
    printf("payload align: %lu\n", end_padding);
    
    // Allouer et initialiser le payload avec le padding nécessaire
    uint8_t *payload = (uint8_t *)malloc(packer->payload_64_size + offset_padding + end_padding);
    if (!payload)
        return NULL;
    
    ft_bzero(payload, offset_padding); // Nettoyer le padding
    ft_memcpy(payload + offset_padding, packer->payload_64, packer->payload_64_size); // Copier le payload
	ft_memcpy(payload + offset_padding + packer->payload_64_size - WD_PAYLOAD_OFF_KEY, key_aes, WD_AES_KEY_SIZE); // Copier le payload

    ft_bzero(payload + offset_padding + packer->payload_64_size, end_padding); // Nettoyer le padding à la fin
	
    
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

	uint64_t current_offset = elf->program_headers[last_load_prog].p_offset + elf->program_headers[last_load_prog].p_memsz;
    uint64_t current_vaddr = elf->program_headers[last_load_prog].p_vaddr + elf->program_headers[last_load_prog].p_memsz;

	uint64_t offset_padding = new_section->sh_addralign - (current_offset % new_section->sh_addralign);
	uint64_t vaddr_padding = new_section->sh_addralign - (current_vaddr % new_section->sh_addralign);

	if (current_offset % new_section->sh_addralign != 0) {
        current_offset += offset_padding;
    }
    if (current_vaddr % new_section->sh_addralign != 0) {
        current_vaddr += vaddr_padding;
    }
	
	new_section->sh_offset = current_offset;
    new_section->sh_address = current_vaddr;
	packer->loader_offset = new_section->sh_address;

	if ((new_section->data = prepare_payload(new_section, packer)) == NULL)
	{
		free(new_section);
		return (-1);
	}

	new_section->sh_size = packer->payload_64_size;
    if (packer->payload_64_size % new_section->sh_addralign != 0) {
        new_section->sh_size += new_section->sh_addralign - (packer->payload_64_size % new_section->sh_addralign);
    }

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

void	update_program_header(t_elf_file *elf, t_packer *packer, int last_loadable)
{
	size_t new_segment_size = elf->program_headers[last_loadable].p_memsz + packer->payload_64_size;
	elf->program_headers[last_loadable].p_memsz = new_segment_size;
	elf->program_headers[last_loadable].p_filesz = new_segment_size;

	for (int i = 0; i < elf->e_phnum; i++) {
		if (elf->program_headers[i].p_type == PT_LOAD) {
			elf->program_headers[i].p_flags = PF_X | PF_W | PF_R; // NOLINT(hicpp-signed-bitwise)
		}
	}
}

void	update_section_addr(t_elf_file *elf, t_packer *packer, int last_loadable)
{
	for (int i = last_loadable; i < elf->e_shnum - 1; i++) {
		// printf("%s:\n", elf->section_tables[i].sh_name);
		// printf("%s:\n", elf->section_tables[i+1].sh_name);
		if (elf->section_tables[i].sh_type == SHT_NOBITS) {
			elf->section_tables[i + 1].sh_offset = elf->section_tables[i].sh_offset;
			continue;
		}
		// printf("%#lx, %lx, t %#lx | align %d\n", elf->section_tables[i].sh_offset, elf->section_tables[i].sh_size, elf->section_tables[i].sh_offset + elf->section_tables[i].sh_size, elf->section_tables[i + 1].sh_addralign);
		uint64_t offset_padding = elf->section_tables[i + 1].sh_addralign > 1 ?
			elf->section_tables[i + 1].sh_addralign - (elf->section_tables[i].sh_offset + elf->section_tables[i].sh_size) % elf->section_tables[i + 1].sh_addralign
			: 0;
		// printf("offset_padding: %lu\n", offset_padding);
		elf->section_tables[i + 1].sh_offset = elf->section_tables[i].sh_offset + elf->section_tables[i].sh_size + offset_padding;
	}

	int section_count = elf->e_shnum;
	elf->e_shoff = elf->section_tables[section_count - 1].sh_offset + elf->section_tables[section_count - 1].sh_size;
}

void	update_entry_point(t_elf_file *elf, t_packer *packer, int last_loadable)
{
	uint64_t last_entry_point = elf->e_entry;
	elf->e_entry = elf->section_tables[last_loadable].sh_address;

	uint64_t jmp_instruction_address = elf->e_entry + packer->payload_64_size - WD_PAYLOAD_RETURN_ADDR;
    uint64_t next_instruction_address = jmp_instruction_address;
	int32_t offset = (int32_t)(last_entry_point - next_instruction_address);

	ft_memcpy(elf->section_tables[last_loadable].data + packer->payload_64_size - WD_PAYLOAD_RETURN_ADDR, &offset, sizeof(offset));
}

int	elf_insert_section(t_elf_file *elf)
{
	t_packer	packer;
	packer.payload_64_size = WB_PAYLOAD_SIZE;
	packer.payload_64 = (uint8_t *)wd_playload_64;
	
	int progi = efl_find_last_prog_header(elf);
	int sectioni = efl_find_last_section_header(elf, progi);
	if (create_new_elf_section(elf, &packer, progi, sectioni) == -1)
		return (-1);

	sectioni += 1;
	update_program_header(elf, &packer, progi);
	update_section_addr(elf, &packer, sectioni);
	update_entry_point(elf, &packer, sectioni);
	return (0);
}
