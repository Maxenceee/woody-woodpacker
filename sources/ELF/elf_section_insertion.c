/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf_section_insertion.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 18:37:53 by mgama             #+#    #+#             */
/*   Updated: 2024/07/30 12:50:13 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"
#include <stdio.h>

size_t calculate_padding(size_t size, size_t alignment)
{
	if (alignment == 0)
		return (0);
	size_t padding = (alignment - (size % alignment)) % alignment;
	return (padding);
}

size_t calculate_padded_size(size_t size, size_t alignment)
{
	size_t padding = (alignment - (size % alignment)) % alignment;
	return (size + padding);
}

int	has_section(t_elf_file *elf, const char *name)
{
	for (int i = 0; i < elf->e_shnum; i++) {
		if (elf->section_tables[i].sh_name && ft_strcmp(elf->section_tables[i].sh_name, name) == 0) {
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
		if (elf->section_tables[j].sh_address >= prog->p_vaddr
				&& elf->section_tables[j].sh_address < prog->p_vaddr + prog->p_memsz)
		{
			index = j;
		}
	}
	return (index);
}

uint8_t	*prepare_payload(t_elf_section *new_section, t_elf_section *text_section, t_packer *packer)
{
	uint8_t	*payload = (uint8_t *)malloc(packer->payload_size);
	if (!payload)
		return (NULL);

	ft_memcpy(payload, packer->payload, packer->payload_size);
	// Copy key inside payload
	ft_memcpy(payload + packer->payload_size - WD_PAYLOAD_OFF_KEY, key_aes, WD_AES_KEY_SIZE);

	ft_memcpy(payload + packer->payload_size - WD_PAYLOAD_OFF_DATA_START, &new_section->sh_address, sizeof(uint64_t));
	ft_memcpy(payload + packer->payload_size - WD_PAYLOAD_OFF_DATA_SIZE, &text_section->sh_size, sizeof(uint64_t));
	ft_memcpy(payload + packer->payload_size - WD_PAYLOAD_OFF_DATA_ADDR, &text_section->sh_address, sizeof(uint64_t));
	return (payload);
}

char *generate_section_name(const char *base_name, int suffix) {
	size_t base_len = ft_strlen(base_name);
	size_t new_len = base_len + 1 + snprintf(NULL, 0, "%d", suffix) + 1; // base + '-' + suffix_length + null terminator
	char *new_name = malloc(new_len);
	if (new_name == NULL)
	{
		return (NULL);
	}
	snprintf(new_name, new_len, "%s-%d", base_name, suffix);
	return (new_name);
}

int	set_new_elf_section_string_table(t_elf_file *elf, t_elf_section *new_section)
{
	char *section_name = malloc(sizeof(WB_SECTION_NAME));
	if (section_name == NULL) {
		return (-1);
	}
	ft_memcpy(section_name, WB_SECTION_NAME, sizeof(WB_SECTION_NAME));

	/**
	 * If a section with the same name already exists, we append a number to the
	 * section name to make it unique.
	 */
	int suffix = 2;
	while (has_section(elf, section_name))
	{
		char *new_name = generate_section_name(WB_SECTION_NAME, suffix);
		free(section_name);
		if (new_name == NULL)
		{
			return (-1);
		}
		section_name = new_name;
		suffix++;
	}

	size_t section_name_len = ft_strlen(section_name) + 1;

	int section_string_table_index = elf->e_shstrndx;
	int old_size = elf->section_tables[section_string_table_index].sh_size;

	size_t new_string_table_size = old_size + section_name_len;
	void *tmp = malloc(new_string_table_size);
	if (tmp == NULL)
	{
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

int	create_new_elf_section(t_elf_file *elf, t_packer *packer, int last_loadable, int last_section_in_prog)
{
	elf->e_shnum += 1;

	ft_verbose("\nCreating new section...\n");
	size_t new_section_headers_size = sizeof(t_elf_section) * elf->e_shnum;
	void *tmp = malloc(new_section_headers_size);
	if (tmp == NULL)
	{
		return (-1);
	}
	ft_memcpy(tmp, elf->section_tables, sizeof(t_elf_section) * (elf->e_shnum - 1));
	free(elf->section_tables);
	elf->section_tables = tmp;
	ft_memset(&elf->section_tables[elf->e_shnum - 1], 0, sizeof(t_elf_section)); // Initialize the new section in case of error during the creation

	t_elf_section *new_section = ft_calloc(1, sizeof(t_elf_section));
	if (new_section == NULL)
		return (-1);

	new_section->sh_type = SHT_PROGBITS;
	new_section->sh_flags = SHF_EXECINSTR | SHF_ALLOC;
	new_section->sh_addralign = 16;

	/**
	 * The section offset must be aligned with its alignment value, as the size of the
	 * pretending section is not necessarily a multiple of its alignment, a padding is
	 * calculated to correct the potential gap.
	 */
	uint64_t current_offset_padding = calculate_padding(elf->program_headers[last_loadable].p_offset + elf->program_headers[last_loadable].p_memsz, new_section->sh_addralign);
	uint64_t current_offset = elf->program_headers[last_loadable].p_offset + elf->program_headers[last_loadable].p_memsz + current_offset_padding;

	/**
	 * Same the section address.
	 */
	uint64_t current_vaddr_padding = calculate_padding(elf->program_headers[last_loadable].p_vaddr + elf->program_headers[last_loadable].p_memsz, new_section->sh_addralign);
	uint64_t current_vaddr = elf->program_headers[last_loadable].p_vaddr + elf->program_headers[last_loadable].p_memsz + current_vaddr_padding;
	
	new_section->sh_offset = current_offset;
	new_section->sh_address = current_vaddr;
	packer->new_section_size = current_offset_padding + WB_PAYLOAD_SIZE;

	ft_verbose("New section offset: %#x\n", new_section->sh_offset);
	ft_verbose("New section address: %#x\n", new_section->sh_address);

	packer->loader_offset = new_section->sh_address;

	ft_verbose("Extracting text section...\n");
	t_elf_section *text_section = get_text_section(elf);
	if (text_section == NULL)
	{
		ft_error("The text section could not be found in the file");
		free(new_section);
		return (-1);
	}
	ft_verbose("Text section found\n");
	ft_verbose("Copying payload data into new section...\n");
	if ((new_section->data = prepare_payload(new_section, text_section, packer)) == NULL)
	{
		free(new_section);
		return (-1);
	}
	ft_verbose("Payload data copied\n");

	new_section->sh_size = packer->payload_size;
	/**
	 * The true size of the section might not be a multiple of its alignment value,
	 * a padding is calculated to correct the potential gap and we save it to be used
	 * later to remap the section headers.
	 */
	// packer->new_section_size += calculate_padded_size(packer->payload_size, new_section->sh_addralign);
	ft_verbose("New section size: %#x (%d bytes)\n", new_section->sh_size, new_section->sh_size);

	size_t remaining_after_section_headers_data_size = sizeof(t_elf_section) * (elf->e_shnum - last_section_in_prog - 1 - 1);

	ft_verbose("Moving section headers...\n");
	ft_memmove(elf->section_tables + last_section_in_prog + 2, elf->section_tables + last_section_in_prog + 1, remaining_after_section_headers_data_size);

	last_section_in_prog += 1;
	ft_memset(&elf->section_tables[last_section_in_prog], 0, sizeof(t_elf_section));

	if (elf->e_shstrndx != 0)
	{
		if (elf->e_shstrndx >= last_section_in_prog) {
			elf->e_shstrndx += 1;
		}

		ft_verbose("Updating section string table...\n");
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
		(void)ft_warning("No section string table found");
	}

	ft_verbose("Updating section headers...\n");
	ft_memcpy(&elf->section_tables[last_section_in_prog], new_section, sizeof(t_elf_section));
	ft_verbose("New section copied\n");

	ft_verbose("Updating symbol table...\n");
	for (int i = 0; i < elf->e_shnum; i++) {
		if (ft_strcmp(elf->section_tables[i].sh_name, ".symtab") == 0) {
			elf->section_tables[i].sh_link += 1;
		}
	}
	ft_verbose(B_GREEN"\nNew section successfully created\n"RESET);
	free(new_section);
	return (0);
}

void	update_program_header(t_elf_file *elf, t_packer *packer, int last_loadable)
{
	ft_verbose("\nUpdating program header...\n");
	ft_verbose("Last loadable segment: %d\n", last_loadable);

	size_t new_segment_size = elf->program_headers[last_loadable].p_memsz + packer->new_section_size;
	elf->program_headers[last_loadable].p_memsz = new_segment_size;
	elf->program_headers[last_loadable].p_filesz = new_segment_size;
	ft_verbose("New program header size: %#x\n", elf->program_headers[last_loadable].p_memsz);

	/**
	 * Add reading and exectuting permission to the program header containing our section
	 */
	elf->program_headers[last_loadable].p_flags |= PF_R | PF_X;
	for (int i = 0; i < elf->e_phnum; i++)
	{
		/**
		 * Since we will write in runtime in .text section we must add wrting permission
		 */
		if (elf->program_headers[i].p_type == PT_LOAD && elf->program_headers[i].p_flags & PF_X)
			elf->program_headers[i].p_flags |=  PF_W;
	}
}

void	update_section_addr(t_elf_file *elf, int last_loadable)
{
	ft_verbose("\nUpdating section addresses...\n");
	/**
	 * Since we added a new section, we need to update the offset of the following sections.
	 * For each section, the new offset is the offset of the last section plus its size
	 * and the padding needed to align the next section.
	 */
	for (int i = last_loadable; i < elf->e_shnum - 1; i++) {
		ft_verbose("Updating %s%s%s (%d) section offset\n", B_CYAN, elf->section_tables[i + 1].sh_name, RESET, i + 1);
	
		/**
		 * It the last section is SHT_NOBITS, we don't need to add its size to the offset of the next section.
		 */
		if (elf->section_tables[i].sh_type == SHT_NOBITS) {
			elf->section_tables[i + 1].sh_offset = elf->section_tables[i].sh_offset;
			ft_verbose("  Previous section is SHT_NOBITS\n");
			if (elf->section_tables[i + 1].sh_address != 0)
				elf->section_tables[i + 1].sh_address = elf->section_tables[i].sh_address;
			ft_verbose("  New offset: %#x\n", elf->section_tables[i + 1].sh_offset);
			ft_verbose("  New address: %#x\n", elf->section_tables[i + 1].sh_address);
			continue;
		}

		/**
		 * Calculate the padding needed to align the next section based on the offset and size of
		 * the last section and the alignment of the current section.
		 */
		uint64_t offset_padding = calculate_padded_size(
			elf->section_tables[i].sh_offset + elf->section_tables[i].sh_size, 
			elf->section_tables[i + 1].sh_addralign
		) - (elf->section_tables[i].sh_offset + elf->section_tables[i].sh_size);
		ft_verbose("  Previous offset: %#x\n", elf->section_tables[i + 1].sh_offset);
		ft_verbose("  Previous address: %#x\n", elf->section_tables[i + 1].sh_address);
		ft_verbose("  Section offset padding: %d\n", offset_padding);

		elf->section_tables[i + 1].sh_offset = elf->section_tables[i].sh_offset + elf->section_tables[i].sh_size + offset_padding;
		if (elf->section_tables[i + 1].sh_address != 0)
			elf->section_tables[i + 1].sh_address = elf->section_tables[i].sh_address + elf->section_tables[i].sh_size + offset_padding;
		ft_verbose("  New offset: %#x\n", elf->section_tables[i + 1].sh_offset);
		ft_verbose("  New address: %#x\n", elf->section_tables[i + 1].sh_address);
	}

	/**
	 * Once all the sections have been updated, we need to update the section headers offset.
	 */
	int section_count = elf->e_shnum;
	elf->e_shoff = elf->section_tables[section_count - 1].sh_offset + elf->section_tables[section_count - 1].sh_size;
	ft_verbose("New section headers offset: %#x\n", elf->e_shoff);
}

void	update_entry_point(t_elf_file *elf, t_packer *packer, int last_loadable)
{
	ft_verbose("\nUpdating entry point...\n");
	uint64_t last_entry_point = elf->e_entry;
	elf->e_entry = elf->section_tables[last_loadable].sh_address;
	ft_verbose("Last entry point: %#x\n", last_entry_point);
	ft_verbose("New entry point: %#x\n", elf->e_entry);

	/**
	 * To calculate the offset from the jump instruction to the previous entry point, we need to
	 * know the address of the jump instruction and the address of the instruction after the jump.
	 */
	uint64_t jmp_instruction_address = elf->e_entry + packer->payload_size - WD_PAYLOAD_RETURN_ADDR;
	uint64_t next_instruction_address = jmp_instruction_address + 4; // + 4 bytes to go to the address of the instruction after jump
	int32_t offset = (int32_t)(last_entry_point - next_instruction_address);

	ft_memcpy(elf->section_tables[last_loadable].data + packer->payload_size - WD_PAYLOAD_RETURN_ADDR, &offset, sizeof(offset));
}

void	update_symbols_table(t_elf_file *elf, int symtab_idx, int symstr_idx)
{
	t_elf_sym sym;
	for (size_t j = 0; j * sizeof(t_elf_sym) < elf->section_tables[symtab_idx].sh_size; j++) {
		void *absoffset = elf->section_tables[symtab_idx].data + j * sizeof(t_elf_sym);
		ft_memmove(&sym, absoffset, sizeof(sym));

		if (sym.st_name == 0)
			continue;

		/**
		 * If debug flag is set, we update the `_start` symbol to point to the new entry point.
		 */
		if (ft_strcmp((char *)(elf->section_tables[symstr_idx].data + sym.st_name), "_start") == 0)
		{
			ft_verbose("Updating %s%s%s symbol\n", B_CYAN, "_start", RESET);
			sym.st_value = elf->e_entry;
			ft_verbose("New symbol value: %#x\n", sym.st_value);
			ft_memmove(absoffset, &sym, sizeof(sym));
			break;
		}
	}
}

void	update_symbols(t_elf_file *elf)
{
	int symstr_idx = 0;
	int symtab_idx = 0;

	ft_verbose("\nUpdating symbol table...\n");
	for (uint16_t i = 0; i < elf->e_shnum; i++) {
		if (ft_strcmp(elf->section_tables[i].sh_name, ".symtab") == 0 && elf->section_tables[i].sh_type == SHT_SYMTAB)
			symtab_idx = i;
		else if (ft_strcmp(elf->section_tables[i].sh_name, ".strtab") == 0 && elf->section_tables[i].sh_type == SHT_STRTAB)
			symstr_idx = i;
	}
	if (symtab_idx == 0 || symstr_idx == 0)
	{
		ft_warning("Could not update '.symtab' symbol table");
	}
	else
	{
		ft_verbose("\nUpdating '.symtab' symbol table...\n");
		update_symbols_table(elf, symtab_idx, symstr_idx);
	}
	
	for (uint16_t i = 0; i < elf->e_shnum; i++) {
		if (ft_strcmp(elf->section_tables[i].sh_name, ".dynsym") == 0 && elf->section_tables[i].sh_type == SHT_DYNSYM)
			symtab_idx = i;
		else if (ft_strcmp(elf->section_tables[i].sh_name, ".dynstr") == 0 && elf->section_tables[i].sh_type == SHT_STRTAB)
			symstr_idx = i;
	}
	if (symtab_idx == 0 || symstr_idx == 0)
	{
		ft_warning("Could not update '.dynsym' symbol table");
	}
	else
	{
		ft_verbose("\nUpdating '.dynsym' symbol table...\n");
		update_symbols_table(elf, symtab_idx, symstr_idx);
	}
}

int	elf_insert_section(t_elf_file *elf, int opt)
{
	t_packer	packer;
	packer.payload_size = WB_PAYLOAD_SIZE;
	packer.payload = (uint8_t *)wd_playload;
	packer.new_section_size = 0;
	ft_verbose("\nStarting new section insertion...\n");
	ft_verbose("Payload: %p\n", packer.payload);
	ft_verbose("Payload size: %u bytes\n", packer.payload_size);
	
	int progi = efl_find_last_prog_header(elf);
	ft_verbose("Last loadable program header index: %d\n", progi);
	int sectioni = efl_find_last_section_header(elf, progi);
	ft_verbose("Last loadable section header index: %d\n", sectioni);
	if (create_new_elf_section(elf, &packer, progi, sectioni) == -1)
		return (-1);

	sectioni += 1;
	update_program_header(elf, &packer, progi);
	update_section_addr(elf, sectioni);
	update_entry_point(elf, &packer, sectioni);

	if (opt & F_UDSYM)
		update_symbols(elf);
	return (0);
}
