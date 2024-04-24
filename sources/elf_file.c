/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:11:26 by mbrement          #+#    #+#             */
/*   Updated: 2024/04/24 16:46:25 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

static void	get_type_name(t_binary_reader *reader, t_elf_file *elf_file)
{
	reader->seek(reader, 16);
	elf_file->e_type = reader->get_uint8(reader);
	 switch(elf_file->e_type) {
		case 0x00 :
			elf_file->e_type_name = "ET_NONE";
			break;
		case 0x01 :
			elf_file->e_type_name = "ET_REL";
			break;
		case 0x02 :
			elf_file->e_type_name = "ET_EXEC";
			break;
		case 0x03 :
			elf_file->e_type_name = "ET_DYN";
			break;
		case 0x04 :
			elf_file->e_type_name = "ET_CORE";
			break;
		case 0xFE00 :
			elf_file->e_type_name = "ET_LOOS";
			break;
		case 0xFEFF :
			elf_file->e_type_name = "ET_HIOS";
			break;
		case 0xFF00 :
			elf_file->e_type_name = "ET_LOPROC";
			break;
		case 0xFFFF :
			elf_file->e_type_name = "ET_HIPROC";
            break;
        default:
			elf_file->e_type_name = "Error";
    }
}

int	get_elf_tables_offset(t_elf_file *elf_file, t_binary_reader *reader)
{
	reader->seek(reader, elf_file->e_shoff);
	elf_file->section_tables = ft_calloc(1, sizeof(t_elf_section_table));
	if (elf_file->section_tables == NULL)
		return (ft_error(WD_PREFIX"Could not allocate memory.\n"), 1);
	for (int i = 0; i < elf_file->e_shnum; i++)
	{
		(void)reader->get_uint32(reader);
		elf_file->section_tables[i].sh_type = reader->get_uint32(reader);
		if (elf_file->e_ident_class == WD_32BITS)
		{
			elf_file->section_tables[i].sh_flags = reader->get_uint32(reader);
			elf_file->section_tables[i].sh_address = reader->get_uint32(reader);
			elf_file->section_tables[i].sh_offset = reader->get_uint32(reader);
			elf_file->section_tables[i].sh_size = reader->get_uint32(reader);
		}
		else
		{
			elf_file->section_tables[i].sh_flags = reader->get_uint64(reader);
			elf_file->section_tables[i].sh_address = reader->get_uint64(reader);
			elf_file->section_tables[i].sh_offset = reader->get_uint64(reader);
			elf_file->section_tables[i].sh_size = reader->get_uint64(reader);
		}
	}
	return (0);
}

t_elf_file	*new_elf_file(t_binary_reader *reader)
{
	t_elf_file *elf_file = ft_calloc(1, sizeof(t_elf_file));
	if (elf_file == NULL)
		return (ft_error(WD_PREFIX"Could not allocate memory.\n"), NULL);
	reader->seek(reader, 1);
	elf_file->e_ident_mag = reader->get_string(reader, 3);
	elf_file->e_ident_class = reader->get_uint8(reader) * 32;

	if (ft_strcmp(elf_file->e_ident_mag, "ELF") == 0)
	{
		elf_file->correcte_ident_mag = 1;
	}

	elf_file->e_ident_data = reader->get_uint8(reader);
	elf_file->e_ident_data_type = elf_file->e_ident_data - 1 ? "big endian" : "little endian";
	if (elf_file->e_ident_data == 1)
	{
		reader->set_endian(reader, READER_LITTLE_ENDIAN);
	}

	/**
	 * We check that the e_ident version is 1, if not the file is not valid
	 */
	if (reader->get_uint8(reader) != 1)
	{
		delete_elf_file(elf_file);
		return (ft_error(WD_PREFIX"Wrong version.\n"), NULL);
	}

	elf_file->e_ident_osabi =  reader->get_uint8(reader);
	if (elf_file->e_ident_osabi != 0x00 && elf_file->e_ident_osabi != 0x03)
	{
		delete_elf_file(elf_file);
		return (ft_error(WD_PREFIX"Invlide ABI.\n"), NULL);
	}
	get_type_name(reader, elf_file);

	reader->seek(reader, 0x18);
	if (elf_file->e_ident_class == WD_32BITS)
	{
		elf_file->e_entry += reader->get_uint32(reader);
		elf_file->e_shoff = reader->get_uint32(reader);
		elf_file->e_phoff = reader->get_uint32(reader);
	}
	else
	{
		elf_file->e_entry += reader->get_uint64(reader);
		elf_file->e_shoff = reader->get_uint64(reader);
		elf_file->e_phoff = reader->get_uint64(reader);
	}

	(void)reader->get_uint32(reader);
	elf_file->e_ehsize = reader->get_uint16(reader);
	elf_file->e_phentsize = reader->get_uint16(reader);
	elf_file->e_phnum = reader->get_uint16(reader);
	elf_file->e_shentsize = reader->get_uint16(reader);
	elf_file->e_shnum = reader->get_uint16(reader);
	elf_file->e_shstrndx = reader->get_uint16(reader);

	if (get_elf_tables_offset(elf_file, reader))
	{
		delete_elf_file(elf_file);
		return (ft_error(WD_PREFIX"Could not allocate memory.\n"), NULL);
	}

	return (elf_file);
}

void	delete_elf_file(t_elf_file *elf_file)
{
	free(elf_file->e_ident_mag);
	free(elf_file);
}

void	print_elf_file(t_elf_file *elf_file)
{
	printf("Magic:                             %s\n", elf_file->e_ident_mag);
	printf("Class:                             %s%d\n", elf_file->e_ident_mag, elf_file->e_ident_class);
	printf("Data:                              2's complement, %s\n", elf_file->e_ident_data_type);
	printf("Version:                           1 (current)\n");
	printf("OS/ABI:                            %#x\n", elf_file->e_ident_osabi);
	printf("Type:                              %s\n", elf_file->e_type_name);
	printf("Entry point:                       %#llx\n", elf_file->e_entry);
	printf("Start of program headers:          %lld (bytes into file)\n", elf_file->e_phoff);
	printf("Start of section headers:          %lld (bytes into file)\n", elf_file->e_shoff);
	printf("Size of this header:               %lld (bytes)\n", elf_file->e_ehsize);
	printf("Size of program headers:           %d (bytes)\n", elf_file->e_phentsize);
	printf("Number of program headers:         %d\n", elf_file->e_phnum);
	printf("Size of section headers:           %d (bytes)\n", elf_file->e_shentsize);
	printf("Number of section headers:         %d\n", elf_file->e_shnum);
	printf("Section header string table index: %d\n", elf_file->e_shstrndx);
}