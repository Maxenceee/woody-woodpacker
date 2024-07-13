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
#include "ctype.h"

static void	get_type_name(t_binary_reader *reader, t_elf_file *elf_file)
{
	reader->seek(reader, 0x10);
	elf_file->e_type = reader->get_uint16(reader);
	 switch(elf_file->e_type) {
		case 0x00 :
			elf_file->e_type_name = "NONE";
			break;
		case 0x01 :
			elf_file->e_type_name = "REL";
			break;
		case 0x02 :
			elf_file->e_type_name = "EXEC";
			break;
		case 0x03 :
			elf_file->e_type_name = "DYN";
			break;
		case 0x04 :
			elf_file->e_type_name = "CORE";
			break;
		case 0xFE00 :
			elf_file->e_type_name = "LOOS";
			break;
		case 0xFEFF :
			elf_file->e_type_name = "HIOS";
			break;
		case 0xFF00 :
			elf_file->e_type_name = "LOPROC";
			break;
		case 0xFFFF :
			elf_file->e_type_name = "HIPROC";
            break;
        default:
			elf_file->e_type_name = "Error"; 
    }
}

static int	get_elf_tables_offset(t_elf_file *elf_file, t_binary_reader *reader)
{
	reader->seek(reader, elf_file->e_shoff);
	elf_file->section_tables = ft_calloc(elf_file->e_shnum, sizeof(t_elf_section_table));
	if (elf_file->section_tables == NULL)
		return (ft_error(WD_PREFIX"Could not allocate memory.\n"), 1);
	for (int i = 0; i < elf_file->e_shnum; i++)
	{
		elf_file->section_tables[i].sh_name_offset = reader->get_uint32(reader);
		elf_file->section_tables[i].sh_type = reader->get_uint32(reader);
		if (elf_file->e_ident.ei_class == WD_32BITS)
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
		elf_file->section_tables[i].sh_link = reader->get_uint32(reader);
		elf_file->section_tables[i].sh_info = reader->get_uint32(reader);
		if (elf_file->e_ident.ei_class == WD_32BITS)
		{
			elf_file->section_tables[i].sh_addralign = reader->get_uint32(reader);
			elf_file->section_tables[i].sh_entsize = reader->get_uint32(reader);
		}
		else
		{
			elf_file->section_tables[i].sh_addralign = reader->get_uint64(reader);
			elf_file->section_tables[i].sh_entsize = reader->get_uint64(reader);
		}
	}
	if (elf_file->e_shstrndx > 0)
	{
		for (int i = 0; i < elf_file->e_shnum; i++)
		{
			reader->seek(reader, elf_file->section_tables[elf_file->e_shstrndx].sh_offset + elf_file->section_tables[i].sh_name_offset);
			elf_file->section_tables[i].sh_name = reader->get_rstring(reader);
			if (elf_file->section_tables[i].sh_name == NULL)
				return (ft_error(WD_PREFIX"Could not allocate memory.\n"), 1);
		}
	}

	size_t elf_section_data_size;
	for (int i = 0; i < elf_file->e_shnum; i++)
	{
		if (elf_file->section_tables[i].sh_type != SHT_NOBITS) {
			elf_section_data_size = elf_file->section_tables[i].sh_size;

			elf_file->section_tables[i].data = malloc(elf_section_data_size);
			if (elf_file->section_tables[i].data == NULL) {
				free(elf_file->section_tables[i].data);
				return (ft_error(WD_PREFIX"Could not allocate memory.\n"), 1);
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
	reader->seek(reader, elf_file->e_phoff);
	elf_file->program_headers = ft_calloc(elf_file->e_phnum, sizeof(t_elf_program_header));
	if (elf_file->program_headers == NULL)
		return (ft_error(WD_PREFIX"Could not allocate memory.\n"), 1);
	for (int i = 0; i < elf_file->e_phnum; i++)
	{
		elf_file->program_headers[i].p_type = reader->get_uint32(reader);
		if (elf_file->e_ident.ei_class == WD_32BITS)
		{
			elf_file->program_headers[i].p_offset = reader->get_uint32(reader);
			elf_file->program_headers[i].p_vaddr = reader->get_uint32(reader);
			elf_file->program_headers[i].p_paddr = reader->get_uint32(reader);
			elf_file->program_headers[i].p_filesz = reader->get_uint32(reader);
			elf_file->program_headers[i].p_memsz = reader->get_uint32(reader);
			elf_file->program_headers[i].p_flags = reader->get_uint32(reader);
			elf_file->program_headers[i].p_align = reader->get_uint32(reader);
		}
		else
		{
			elf_file->program_headers[i].p_flags = reader->get_uint32(reader);
			elf_file->program_headers[i].p_offset = reader->get_uint64(reader);
			elf_file->program_headers[i].p_vaddr = reader->get_uint64(reader);
			elf_file->program_headers[i].p_paddr = reader->get_uint64(reader);
			elf_file->program_headers[i].p_filesz = reader->get_uint64(reader);
			elf_file->program_headers[i].p_memsz = reader->get_uint64(reader);
			elf_file->program_headers[i].p_align = reader->get_uint64(reader);
		}
	}
	return (0);
}

t_elf_file	*new_elf_file(t_binary_reader *reader)
{
	t_elf_file *elf_file = ft_calloc(1, sizeof(t_elf_file));
	if (elf_file == NULL)
		return (ft_error(WD_PREFIX"Could not allocate memory.\n"), NULL);

	/**
	 * By default we set en endianness to little endian because it's the endianness of the header
	 */
	reader->set_endian(reader, READER_LITTLE_ENDIAN);
	reader->get_bytes(reader, elf_file->e_ident.raw, 16);

	if (elf_file->e_ident.ei_magic != 0x464C457F) // 0x7F 'E' 'L' 'F' but reversed because of endianness
	{
		delete_elf_file(elf_file);
		return (ft_error(WD_PREFIX"Invalid file format.\n"), NULL);
	}

	if (elf_file->e_ident.ei_data == 2)
	{
		reader->set_endian(reader, READER_BIG_ENDIAN);
	}

	/**
	 * We check that the e_ident version is 1, if not the file is not valid
	 */
	if (elf_file->e_ident.ei_version != 1)
	{
		delete_elf_file(elf_file);
		return (ft_error(WD_PREFIX"Wrong version.\n"), NULL);
	}

	/**
	 * We ensure that the format of the binary matches the current system
	 */
	if (elf_file->e_ident.ei_osabi != 0x00 && elf_file->e_ident.ei_osabi != 0x03)
	{
		delete_elf_file(elf_file);
		return (ft_error(WD_PREFIX"Incompatible ABI.\n"), NULL);
	}

	get_type_name(reader, elf_file);
	elf_file->e_machine = reader->get_uint16(reader);
	elf_file->e_version = reader->get_uint32(reader);

	if (elf_file->e_ident.ei_class == WD_32BITS)
	{
		elf_file->e_entry += reader->get_uint32(reader);
		elf_file->e_phoff = reader->get_uint32(reader);
		elf_file->e_shoff = reader->get_uint32(reader);
	}
	else
	{
		elf_file->e_entry += reader->get_uint64(reader);
		elf_file->e_phoff = reader->get_uint64(reader);
		elf_file->e_shoff = reader->get_uint64(reader);
	}
	elf_file->e_flags = reader->get_uint32(reader);
	elf_file->e_ehsize = reader->get_uint16(reader);
	elf_file->e_phentsize = reader->get_uint16(reader);
	elf_file->e_phnum = reader->get_uint16(reader);
	elf_file->e_shentsize = reader->get_uint16(reader);
	elf_file->e_shnum = reader->get_uint16(reader);
	elf_file->e_shstrndx = reader->get_uint16(reader);

	if (get_elf_tables_offset(elf_file, reader))
	{
		delete_elf_file(elf_file);
		return (NULL);
	}

	if (get_elf_program_headers(elf_file, reader))
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
			free(elf_file->section_tables[i].sh_name);
		}
		free(elf_file->section_tables);
	}
	free(elf_file);
}

static void	print_elf_program_flag(uint32_t flag)
{
	int res = 0;
	if (flag & 0x01)
		res += printf("X");
	if (flag & 0x02)
		res += printf("W");
	if (flag & 0x04)
		res += printf("R");
	printf("%*s%s", 3 - res, "", "    ");
}

void	print_elf_file(t_elf_file *elf_file, int level)
{
	if (level & PELF_ALL || level & PELF_HEADER)
	{
		printf("ELF Header:\n");
		printf("  Magic:   ");
		for (int i = 0; i < 16; i++)
			printf("%02X ", elf_file->e_ident.raw[i]);
		printf("\n");
		printf("  Class:                             ELF%d\n", elf_file->e_ident.ei_class * 32);
		printf("  Data:                              2's complement, %s\n", elf_file->e_ident.ei_data - 1 ? "big endian" : "little endian");
		printf("  Version:                           %u (current)\n", elf_file->e_ident.ei_version);
		printf("  OS/ABI:                            %s\n", g_elf_osabi_name[elf_file->e_ident.ei_osabi]);
		printf("  ABI Version:                       %u\n", elf_file->e_ident.ei_abi_version);
		printf("  Type:                              %s\n", elf_file->e_type_name);
		printf("  Version:                           %#x\n", elf_file->e_version);
		printf("  Entry point:                       %#lx\n", elf_file->e_entry);
		printf("  Start of program headers:          %ld (bytes into file)\n", elf_file->e_phoff);
		printf("  Start of section headers:          %ld (bytes into file)\n", elf_file->e_shoff);
		printf("  Size of this header:               %d (bytes)\n", elf_file->e_ehsize);
		printf("  Size of program headers:           %d (bytes)\n", elf_file->e_phentsize);
		printf("  Number of program headers:         %d\n", elf_file->e_phnum);
		printf("  Size of section headers:           %d (bytes)\n", elf_file->e_shentsize);
		printf("  Number of section headers:         %d\n", elf_file->e_shnum);
		printf("  Section header string table index: %d\n", elf_file->e_shstrndx);
	}

	if (level & PELF_ALL || level & PELF_SECTION)
	{
		printf("\nSection Headers:\n");
		printf("  [Nr] Name               Type               Address            Offset             Size\n");
		for (int i = 0; i < elf_file->e_shnum; i++)
		{
			printf("  [%2d] ", i);
			printf("%-18s", elf_file->section_tables[i].sh_name);
			if (elf_file->section_tables[i].sh_type < 0x13)
				printf("%-18s ", g_elf_section_table_type[elf_file->section_tables[i].sh_type]);
			else
				printf("%#-18x ", elf_file->section_tables[i].sh_type);
			printf("%#018lx ", elf_file->section_tables[i].sh_address);
			printf("%#018lx ", elf_file->section_tables[i].sh_offset);
			printf("%#018lx\n", elf_file->section_tables[i].sh_size);
		}

		printf("\nProgram Headers:\n");
		printf("  Type           Offset             VirtAddr           PhysAddr           FileSiz            MemSiz             Flags  Align\n");
		for (int i = 0; i < elf_file->e_phnum; i++)
		{
			printf("  ");
			if (elf_file->program_headers[i].p_type < 0x08)
				printf("%-14s ", g_elf_program_header_type[elf_file->program_headers[i].p_type]);
			else
				printf("%#-14x ", elf_file->program_headers[i].p_type);
			printf("%#018lx ", elf_file->program_headers[i].p_offset);
			printf("%#018lx ", elf_file->program_headers[i].p_vaddr);
			printf("%#018lx ", elf_file->program_headers[i].p_paddr);
			printf("%#018lx ", elf_file->program_headers[i].p_filesz);
			printf("%#018lx ", elf_file->program_headers[i].p_memsz);
			print_elf_program_flag(elf_file->program_headers[i].p_flags);
			printf("%#lx\n", elf_file->program_headers[i].p_align);
		}

		printf("\nSection to Segment mapping:\n");
		printf("  Segment Sections...\n");
		for (int i = 0; i < elf_file->e_phnum; i++)
		{
			printf("   %02d     ", i);
			for (int j = 1; j < elf_file->e_shnum; j++)
			{
				if (elf_file->section_tables[j].sh_offset >= elf_file->program_headers[i].p_offset &&
					elf_file->section_tables[j].sh_offset + elf_file->section_tables[j].sh_size <=
					elf_file->program_headers[i].p_offset + elf_file->program_headers[i].p_filesz)
				{
					printf("%s ", elf_file->section_tables[j].sh_name);
				}
			}
			printf("\n");
		}
	}

	if (level & PELF_DATA)
	{
		int tab = 6;
		for (int i = 0; i < elf_file->e_shnum; i++)
		{
			int j = 1, l = elf_file->section_tables[i].sh_size;
			while (l > 10)
			{
				j++;
				l /= 10;
			}
			if (j > tab)
				tab = j;
		}

		char ascii_line[17];
		ascii_line[16] = '\0';
		printf("\nSection data mapping:\n");
		for (int i = 0; i < elf_file->e_shnum; i++)
		{
			if (elf_file->section_tables[i].sh_type != PT_NULL)
				printf("  Section %s:\n", elf_file->section_tables[i].sh_name);
			else
				printf("  Section %s:\n", "(null)");

			if (elf_file->section_tables[i].sh_size == 0 || elf_file->section_tables[i].sh_type == SHT_NOBITS)
			{
				printf("    (null)\n\n");
				continue;
			}

			uint64_t j = 0;
			for (; j < elf_file->section_tables[i].sh_size; j++)
			{
				if (j % 16 == 0)
				{
					printf("    %0*lX: ", tab, j);
				}
				else if (j % 4 == 0)
				{
					printf(" ");
				}
				printf("%02x", elf_file->section_tables[i].data[j]);

				// Stocker le caractère ASCII correspondant
				if (isprint(elf_file->section_tables[i].data[j]))
				{
					ascii_line[j % 16] = elf_file->section_tables[i].data[j];
				}
				else
				{
					ascii_line[j % 16] = '.';
				}

				if ((j + 1) % 16 == 0)
				{
					printf("  %s\n", ascii_line);
				}
			}
			if (j % 16 != 0)
			{
				int remaining = 16 - (j % 16);
				printf("%*s", remaining * 2 + remaining / 4, "");
				for (int k = j % 16; k < 16; k++)
				{
					ascii_line[k] = ' ';
				}
				printf("  %s\n", ascii_line);
			}
			printf("\n");
		}
	}
}
