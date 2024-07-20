/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:11:26 by mbrement          #+#    #+#             */
/*   Updated: 2024/04/24 17:09:42 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

static int	get_elf_tables_offset(t_elf_file *elf_file, t_binary_reader *reader)
{
	ft_verbose("\nReading ELF section tables...\n");
	reader->seek(reader, elf_file->e_shoff);
	elf_file->section_tables = ft_calloc(elf_file->e_shnum, sizeof(t_elf_section));
	if (elf_file->section_tables == NULL)
		return (ft_error("Could not allocate memory"), 1);
	for (int i = 0; i < elf_file->e_shnum; i++)
	{
		elf_file->section_tables[i].sh_name_offset = reader->get_uint32(reader);
		elf_file->section_tables[i].sh_type = reader->get_uint32(reader);
#ifdef WD_32BITS_EXEC
		elf_file->section_tables[i].sh_flags = reader->get_uint32(reader);
		elf_file->section_tables[i].sh_address = reader->get_uint32(reader);
		elf_file->section_tables[i].sh_offset = reader->get_uint32(reader);
		elf_file->section_tables[i].sh_size = reader->get_uint32(reader);
#else
		elf_file->section_tables[i].sh_flags = reader->get_uint64(reader);
		elf_file->section_tables[i].sh_address = reader->get_uint64(reader);
		elf_file->section_tables[i].sh_offset = reader->get_uint64(reader);
		elf_file->section_tables[i].sh_size = reader->get_uint64(reader);
#endif /* WD_32BITS_EXEC */
		elf_file->section_tables[i].sh_link = reader->get_uint32(reader);
		elf_file->section_tables[i].sh_info = reader->get_uint32(reader);
#ifdef WD_32BITS_EXEC
		elf_file->section_tables[i].sh_addralign = reader->get_uint32(reader);
		elf_file->section_tables[i].sh_entsize = reader->get_uint32(reader);
#else
		elf_file->section_tables[i].sh_addralign = reader->get_uint64(reader);
		elf_file->section_tables[i].sh_entsize = reader->get_uint64(reader);
#endif /* WD_32BITS_EXEC */
	}
	ft_verbose("Section table contains %d entries\n", elf_file->e_shnum);
	if (elf_file->e_shstrndx > 0)
	{
		ft_verbose("String table found at index: %d\n", elf_file->e_shstrndx);
		for (int i = 0; i < elf_file->e_shnum; i++)
		{
			reader->seek(reader, elf_file->section_tables[elf_file->e_shstrndx].sh_offset + elf_file->section_tables[i].sh_name_offset);
			elf_file->section_tables[i].sh_name = reader->get_rstring(reader);
			if (elf_file->section_tables[i].sh_name == NULL)
				return (ft_error("Could not allocate memory"), 1);
		}
	}

	size_t elf_section_data_size;
	for (int i = 0; i < elf_file->e_shnum; i++)
	{
		if (elf_file->section_tables[i].sh_type != SHT_NOBITS) {
			elf_section_data_size = elf_file->section_tables[i].sh_size;

			elf_file->section_tables[i].data = malloc(elf_section_data_size);
			if (elf_file->section_tables[i].data == NULL) {
				return (ft_error("Could not allocate memory"), 1);
			}

			ft_memset(elf_file->section_tables[i].data, 0, elf_section_data_size);
			reader->seek(reader, elf_file->section_tables[i].sh_offset);
			reader->get_bytes(reader, elf_file->section_tables[i].data, elf_section_data_size);
		}
	}

	return (0);
}

static int	get_elf_program_headers(t_elf_file *elf_file, t_binary_reader *reader)
{
	ft_verbose("\nReading ELF program headers...\n");
	reader->seek(reader, elf_file->e_phoff);
	elf_file->program_headers = ft_calloc(elf_file->e_phnum, sizeof(t_elf_program_header));
	if (elf_file->program_headers == NULL)
		return (ft_error("Could not allocate memory"), 1);
	for (int i = 0; i < elf_file->e_phnum; i++)
	{
		elf_file->program_headers[i].p_type = reader->get_uint32(reader);
#ifdef WD_32BITS_EXEC
		elf_file->program_headers[i].p_offset = reader->get_uint32(reader);
		elf_file->program_headers[i].p_vaddr = reader->get_uint32(reader);
		elf_file->program_headers[i].p_paddr = reader->get_uint32(reader);
		elf_file->program_headers[i].p_filesz = reader->get_uint32(reader);
		elf_file->program_headers[i].p_memsz = reader->get_uint32(reader);
		elf_file->program_headers[i].p_flags = reader->get_uint32(reader);
		elf_file->program_headers[i].p_align = reader->get_uint32(reader);
#else
		elf_file->program_headers[i].p_flags = reader->get_uint32(reader);
		elf_file->program_headers[i].p_offset = reader->get_uint64(reader);
		elf_file->program_headers[i].p_vaddr = reader->get_uint64(reader);
		elf_file->program_headers[i].p_paddr = reader->get_uint64(reader);
		elf_file->program_headers[i].p_filesz = reader->get_uint64(reader);
		elf_file->program_headers[i].p_memsz = reader->get_uint64(reader);
		elf_file->program_headers[i].p_align = reader->get_uint64(reader);
#endif /* WD_32BITS_EXEC */
	}
	ft_verbose("Program header contains %d entries\n", elf_file->e_phnum);
	return (0);
}

t_elf_file	*new_elf_file(t_binary_reader *reader)
{
	t_elf_file *elf_file = ft_calloc(1, sizeof(t_elf_file));
	if (elf_file == NULL)
		return (ft_error("Could not allocate memory"), NULL);

	ft_verbose("\nStarting file parsing...\n");
	/**
	 * By default we set en endianness to little endian because it's the endianness of the header
	 */
	reader->set_endian(reader, READER_LITTLE_ENDIAN);
	reader->get_bytes(reader, elf_file->e_ident.raw, 16);

	ft_verbose("\nReading ELF magic number...\n");
	ft_verbose("Magic number: %X ", MAGIC(elf_file->e_ident.ei_magic, reader->endian));
	if (elf_file->e_ident.ei_magic != 0x464C457F) // 0x7F 'E' 'L' 'F' but reversed because of endianness
	{
		ft_verbose("%s\n", B_RED"invalid"RESET);
		delete_elf_file(elf_file);
		return (ft_error("Invalid file format"), NULL);
	}

	ft_verbose("%s\n", B_GREEN"valid"RESET);

	ft_verbose("\nReading ELF endianness...\n");
	if (elf_file->e_ident.ei_data == 2)
	{
		reader->set_endian(reader, READER_BIG_ENDIAN);
	}
	ft_verbose("Endianness: %s\n", elf_file->e_ident.ei_data == READER_BIG_ENDIAN ? B_BLUE"Big"RESET : B_CYAN"Little"RESET);

	/**
	 * We check that the e_ident version is 1, if not the file is not valid
	 */
	if (elf_file->e_ident.ei_version != 1)
	{
		delete_elf_file(elf_file);
		return (ft_error("Wrong version"), NULL);
	}

	/**
	 * We ensure that the format of the binary matches the current system
	 */
	if (elf_file->e_ident.ei_osabi != 0x00 && elf_file->e_ident.ei_osabi != 0x03)
	{
		delete_elf_file(elf_file);
		return (ft_error("Incompatible ABI"), NULL);
	}

	ft_verbose("\nReading ELF class...\n");
#ifdef WD_64BITS_EXEC
	if (elf_file->e_ident.ei_class != WD_64BITS)
	{
		delete_elf_file(elf_file);
		return (ft_error("Incompatible class"), NULL);
	}
#else
	if (elf_file->e_ident.ei_class != WD_32BITS)
	{
		delete_elf_file(elf_file);
		return (ft_error("Incompatible class"), NULL);
	}
#endif /* WD_64BITS_EXEC */
	ft_verbose("Class: %s%s%s\n", B_CYAN, elf_file->e_ident.ei_class == WD_32BITS ? "32 bits" : "64 bits", RESET);

	ft_verbose(B_GREEN"\nELF file is valid\n"RESET);

	reader->seek(reader, 0x10);
	elf_file->e_type = reader->get_uint16(reader);
	elf_file->e_machine = reader->get_uint16(reader);
	elf_file->e_version = reader->get_uint32(reader);

#ifdef WD_32BITS_EXEC
	elf_file->e_entry += reader->get_uint32(reader);
	elf_file->e_phoff = reader->get_uint32(reader);
	elf_file->e_shoff = reader->get_uint32(reader);
#else
	elf_file->e_entry += reader->get_uint64(reader);
	elf_file->e_phoff = reader->get_uint64(reader);
	elf_file->e_shoff = reader->get_uint64(reader);
#endif /* WD_32BITS_EXEC */
	elf_file->e_flags = reader->get_uint32(reader);
	elf_file->e_ehsize = reader->get_uint16(reader);
	elf_file->e_phentsize = reader->get_uint16(reader);
	elf_file->e_phnum = reader->get_uint16(reader);
	elf_file->e_shentsize = reader->get_uint16(reader);
	elf_file->e_shnum = reader->get_uint16(reader);
	elf_file->e_shstrndx = reader->get_uint16(reader);

	if (get_elf_program_headers(elf_file, reader))
	{
		delete_elf_file(elf_file);
		return (NULL);
	}

	if (get_elf_tables_offset(elf_file, reader))
	{
		delete_elf_file(elf_file);
		return (NULL);
	}

	return (elf_file);
}

void	delete_elf_file(t_elf_file *elf_file)
{
	if (elf_file == NULL)
		return ;

	if (elf_file->program_headers)
		free(elf_file->program_headers);

	if (elf_file->section_tables)
	{
		for (int i = 0; i < elf_file->e_shnum; i++)
		{
			if (elf_file->section_tables[i].sh_name)
				free(elf_file->section_tables[i].sh_name);
			if (elf_file->section_tables[i].data)
				free(elf_file->section_tables[i].data);
		}
		free(elf_file->section_tables);
	}
	free(elf_file);
}
