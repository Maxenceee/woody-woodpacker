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
		return (ft_error("Could not allocate memory."), 1);
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
				return (ft_error("Could not allocate memory."), 1);
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
				return (ft_error("Could not allocate memory."), 1);
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
		return (ft_error("Could not allocate memory."), 1);
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
		return (ft_error("Could not allocate memory."), NULL);

	/**
	 * By default we set en endianness to little endian because it's the endianness of the header
	 */
	reader->set_endian(reader, READER_LITTLE_ENDIAN);
	reader->get_bytes(reader, elf_file->e_ident.raw, 16);

	if (elf_file->e_ident.ei_magic != 0x464C457F) // 0x7F 'E' 'L' 'F' but reversed because of endianness
	{
		delete_elf_file(elf_file);
		return (ft_error("Invalid file format."), NULL);
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
		return (ft_error("Wrong version."), NULL);
	}

	/**
	 * We ensure that the format of the binary matches the current system
	 */
	if (elf_file->e_ident.ei_osabi != 0x00 && elf_file->e_ident.ei_osabi != 0x03)
	{
		delete_elf_file(elf_file);
		return (ft_error("Incompatible ABI."), NULL);
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
		printf("  OS/ABI:                            ");
		switch (elf_file->e_ident.ei_osabi)
		{
		case 0:
			printf("UNIX - System V\n");
			break;
		case 1:
			printf("HP-UX\n");
			break;
		case 2:
			printf("NetBSD\n");
			break;
		case 3:
			printf("Linux\n");
			break;
		case 4:
			printf("GNU Hurd\n");
			break;
		case 5:
			printf("Solaris\n");
			break;
		case 6:
			printf("AIX (Monterey)\n");
			break;
		case 7:
			printf("IRIX\n");
			break;
		case 8:
			printf("FreeBSD\n");
			break;
		case 9:
			printf("Tru64\n");
			break;
		case 10:
			printf("Novell Modesto\n");
			break;
		case 11:
			printf("OpenBSD\n");
			break;
		case 12:
			printf("OpenVMS\n");
			break;
		case 13:
			printf("NonStop Kernel\n");
			break;
		case 14:
			printf("AROS\n");
			break;
		case 15:
			printf("FenixOS\n");
			break;
		case 16:
			printf("Nuxi CloudABI\n");
			break;
		case 17:
			printf("Stratus Technologies OpenVOS\n");
			break;
		default:
			printf("Unknown\n");
			break;
		}
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
		printf("  [Nr] Name               Type               Address            Offset             Size               Align\n");
		for (int i = 0; i < elf_file->e_shnum; i++)
		{
			printf("  [%*d] ", elf_file->e_shnum / 10 >= 10 ? 3 : 2, i);
			printf("%-18s ", elf_file->section_tables[i].sh_name);
			switch (elf_file->section_tables[i].sh_type)
			{
			case SHT_NULL:
				printf("%-18s ", "NULL");
				break;
			case SHT_PROGBITS:
				printf("%-18s ", "PROGBITS");
				break;
			case SHT_SYMTAB:
				printf("%-18s ", "SYMTAB");
				break;
			case SHT_STRTAB:
				printf("%-18s ", "STRTAB");
				break;
			case SHT_RELA:
				printf("%-18s ", "RELA");
				break;
			case SHT_HASH:
				printf("%-18s ", "HASH");
				break;
			case SHT_DYNAMIC:
				printf("%-18s ", "DYNAMIC");
				break;
			case SHT_NOTE:
				printf("%-18s ", "NOTE");
				break;
			case SHT_NOBITS:
				printf("%-18s ", "NOBITS");
				break;
			case SHT_REL:
				printf("%-18s ", "REL");
				break;
			case SHT_SHLIB:
				printf("%-18s ", "SHLIB");
				break;
			case SHT_DYNSYM:
				printf("%-18s ", "DYNSYM");
				break;
			case SHT_INIT_ARRAY:
				printf("%-18s ", "INIT_ARRAY");
				break;
			case SHT_FINI_ARRAY:
				printf("%-18s ", "FINI_ARRAY");
				break;
			case SHT_PREINIT_ARRAY:
				printf("%-18s ", "PREINIT_ARRAY");
				break;
			case SHT_GROUP:
				printf("%-18s ", "GROUP");
				break;
			case SHT_SYMTAB_SHNDX:
				printf("%-18s ", "SYMTAB_SHNDX");
				break;
			case SHT_NUM:
				printf("%-18s ", "NUM");
				break;
			case SHT_LOOS:
				printf("%-18s ", "LOOS");
				break;
			case SHT_GNU_ATTRIBUTES:
				printf("%-18s ", "GNU_ATTRIBUTES");
				break;
			case SHT_GNU_HASH:
				printf("%-18s ", "GNU_HASH");
				break;
			case SHT_GNU_LIBLIST:
				printf("%-18s ", "GNU_LIBLIST");
				break;
			case SHT_CHECKSUM:
				printf("%-18s ", "CHECKSUM");
				break;
			case SHT_LOSUNW:
				printf("%-18s ", "LOSUNW");
				break;
			case SHT_SUNW_COMDAT:
				printf("%-18s ", "SUNW_COMDAT");
				break;
			case SHT_SUNW_syminfo:
				printf("%-18s ", "SUNW_syminfo");
				break;
			case SHT_GNU_verdef:
				printf("%-18s ", "GNU_verdef");
				break;
			case SHT_GNU_verneed:
				printf("%-18s ", "VERNEED");
				break;
			case SHT_GNU_versym:
				printf("%-18s ", "VERSYM");
				break;
			case SHT_LOPROC:
				printf("%-18s ", "LOPROC");
				break;
			case SHT_HIPROC:
				printf("%-18s ", "HIPROC");
				break;
			case SHT_LOUSER:
				printf("%-18s ", "LOUSER");
				break;
			case SHT_HIUSER:
				printf("%-18s ", "HIUSER");
				break;
			default:
				printf("%#-18x ", elf_file->section_tables[i].sh_type);
				break;
			}
			printf("%#018lx ", elf_file->section_tables[i].sh_address);
			printf("%#018lx ", elf_file->section_tables[i].sh_offset);
			printf("%#018lx ", elf_file->section_tables[i].sh_size);
			printf("%#018lx\n", elf_file->section_tables[i].sh_addralign);
		}
	}

	if (level & PELF_ALL || level & PELF_PROG)
	{
		printf("\nProgram Headers:\n");
		printf("  Type           Offset             VirtAddr           PhysAddr           FileSiz            MemSiz             Flags  Align\n");
		for (int i = 0; i < elf_file->e_phnum; i++)
		{
			printf("  ");
			switch (elf_file->program_headers[i].p_type)
			{
			case PT_NULL:
				printf("%-18s ", "NULL");
				break;
			case PT_LOAD:
				printf("%-18s ", "LOAD");
				break;
			case PT_DYNAMIC:
				printf("%-18s ", "DYNAMIC");
				break;
			case PT_INTERP:
				printf("%-18s ", "INTERP");
				break;
			case PT_NOTE:
				printf("%-18s ", "NOTE");
				break;
			case PT_SHLIB:
				printf("%-18s ", "SHLIB");
				break;
			case PT_PHDR:
				printf("%-18s ", "PHDR");
				break;
			case PT_TLS:
				printf("%-18s ", "TLS");
				break;
			case PT_NUM:
				printf("%-18s ", "NUM");
				break;
			case PT_LOOS:
				printf("%-18s ", "LOOS");
				break;
			case PT_GNU_EH_FRAME:
				printf("%-18s ", "GNU_EH_FRAME");
				break;
			case PT_GNU_STACK:
				printf("%-18s ", "GNU_STACK");
				break;
			case PT_GNU_RELRO:
				printf("%-18s ", "GNU_RELRO");
				break;
			case PT_GNU_PROPERTY:
				printf("%-18s ", "GNU_PROPERTY");
				break;
			case PT_SUNWBSS:
				printf("%-18s ", "SUNWBSS");
				break;
			case PT_SUNWSTACK:
				printf("%-18s ", "SUNWSTACK");
				break;
			case PT_HIOS:
				printf("%-18s ", "HIOS");
				break;
			case PT_LOPROC:
				printf("%-18s ", "LOPROC");
				break;
			case PT_HIPROC:
				printf("%-18s ", "HIPROC");
				break;
			default:
				printf("%#-18x ", elf_file->program_headers[i].p_type);
				break;
			}
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
					elf_file->program_headers[i].p_offset + elf_file->program_headers[i].p_memsz)
				{
					printf("%s ", elf_file->section_tables[j].sh_name);
				}
			}
			printf("\n");
		}
	}

	if (level & PELF_ALL || level & PELF_SYM)
	{
		int symstr_idx = 0;
		int symtab_idx = 0;

		for (uint16_t i = 0; i < elf_file->e_shnum; i++) {
			if (strcmp(elf_file->section_tables[i].sh_name, ".symtab") == 0 && elf_file->section_tables[i].sh_type == SHT_SYMTAB)
				symtab_idx = i;
			else if (strcmp(elf_file->section_tables[i].sh_name, ".strtab") == 0 && elf_file->section_tables[i].sh_type == SHT_STRTAB)
				symstr_idx = i;
		}

		printf("\nSymbol table '.symtab' contains %ld entries:\n", elf_file->section_tables[symtab_idx].sh_size / sizeof(t_elf_sym));
		printf("   Num:    Value          Size Type    Bind   Vis      Ndx Name\n");
		t_elf_sym sym;
		for (size_t j = 0; j * sizeof(t_elf_sym) < elf_file->section_tables[symtab_idx].sh_size; j++) {
			void *absoffset = elf_file->section_tables[symtab_idx].data + j * sizeof(t_elf_sym);
			memmove(&sym, absoffset, sizeof(sym));
			printf("    %2ld: ", j);
			printf("%016lx ", sym.st_value);
			printf("%5ld ", sym.st_size);
			switch (ELF64_ST_TYPE(sym.st_info))
			{
			case STT_NOTYPE:
				printf("%-7s ", "NOTYPE");
				break;
			case STT_OBJECT:
				printf("%-7s ", "OBJECT");
				break;
			case STT_FUNC:
				printf("%-7s ", "FUNC");
				break;
			case STT_SECTION:
				printf("%-7s ", "SECTION");
				break;
			case STT_FILE:
				printf("%-7s ", "FILE");
				break;
			case STT_LOOS:
				printf("%-7s ", "LOOS");
				break;
			case STT_HIOS:
				printf("%-7s ", "HIOS");
				break;
			case STT_LOPROC:
				printf("%-7s ", "LOPROC");
				break;
			case STT_HIPROC:
				printf("%7s ", "HIPROC");
				break;
			default:
				printf("%-7d ", ELF64_ST_TYPE(sym.st_info));
				break;
			}
			switch (ELF64_ST_BIND(sym.st_info))
			{
			case STB_LOCAL:
				printf("%-6s ", "LOCAL");
				break;
			case STB_GLOBAL:
				printf("%-6s ", "GLOBAL");
				break;
			case STB_WEAK:
				printf("%-6s ", "WEAK");
				break;
			case STT_LOOS:
				printf("%-6s ", "LOOS");
				break;
			case STT_HIOS:
				printf("%-6s ", "HIOS");
				break;
			case STT_LOPROC:
				printf("%-6s ", "LOPROC");
				break;
			case STT_HIPROC:
				printf("%-6s ", "HIPROC");
				break;
			default:
				printf("%-6d ", ELF64_ST_BIND(sym.st_info));
				break;
			}
			switch (sym.st_other)
			{
			case STV_DEFAULT:
				printf("%-7s ", "DEFAULT");
				break;
			case STV_INTERNAL:
				printf("%-7s ", "INTERNAL");
				break;
			case STV_HIDDEN:
				printf("%-7s ", "HIDDEN");
				break;
			case STV_PROTECTED:
				printf("%-7s ", "PROTECTED");
				break;
			default:
				printf("%-7d ", sym.st_other);
				break;
			}
			switch (sym.st_shndx)
			{
			case 0:
				printf("%4s ", "UND");
				break;
			case 65521:
				printf("%4s ", "ABS");
				break;
			default:
				printf("%4d ", sym.st_shndx);
				break;
			}
			if (sym.st_name != 0) {
				printf("%s", elf_file->section_tables[symstr_idx].data + sym.st_name);
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
