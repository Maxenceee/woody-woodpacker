/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   woody.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:09:20 by mgama             #+#    #+#             */
/*   Updated: 2024/06/29 17:23:16 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOODY_H
# define WOODY_H

#include <fcntl.h>
#include <stdint.h>
#include <string.h>
# include "reader/binary_reader.h"
# include "writer/binary_writer.h"
# include "AES/aes.h"

#define WD_PREFIX "woody: "

#define WD_MAGIC 0x7F454C46

/**
 * Options
 */

#define F_KEY		0x01
#define F_HEADER	0x02
#define F_SECTION	0x04
#define F_ENCRYPT	0x10
#define F_DECRYPT	0x20


enum e_class {
	WD_32BITS = 1,
	WD_64BITS = 2
};

enum e_program_header_type {
	PT_NULL				= 0,
	PT_LOAD				= 1,
	PT_DYNAMIC			= 2,
	PT_INTERP			= 3,
	PT_NOTE				= 4,
	PT_SHLIB			= 5,
	PT_TLS				= 7,
	PT_PHDR				= 6,
	PT_NUM				= 8,
	PT_LOOS				= 9,
	PT_LOSUNW			= 0x6ffffffa,
	PT_SUNWBSS			= 0x6ffffffb,
	PT_SUNWSTACK		= 0x6ffffffc,
	PT_HIOS				= 0x6fffffff,
	PT_LOPROC			= 0x70000000,
	PT_HIPROC			= 0x7fffffff
};

/*
 * Structures
 */

typedef struct s_elf_file			t_elf_file;
typedef struct s_elf_section_table	t_elf_section_table;
typedef struct s_elf_program_header	t_elf_program_header;

struct s_elf_file {
	union u_elf_e_ident
	{
		struct {
			uint32_t	ei_magic;				// magic number
			uint8_t		ei_class;				// 32 bits or 64 bits
			uint8_t		ei_data;				// little of big endian
			uint8_t		ei_version;				// elf version
			uint8_t		ei_osabi;				// operating system target
			uint8_t		ei_abi_version;			// abi version
			char		ei_pad[7];				// Reserved padding bytes
		};

		char		raw[16];
	} e_ident;

	uint16_t	e_type;						// object type
	char		*e_type_name;
	uint16_t	e_machine;					// machine type
	uint32_t	e_version;					// object version
	uint64_t	e_entry;					// address where the execution starts
	uint64_t	e_phoff;					// program headers' offset
	uint64_t	e_shoff;					// section headers' offset
	uint32_t	e_flags;					// architecture-specific flags
	uint64_t	e_ehsize;					// elf header size
	uint16_t	e_phentsize; 				// size of a single program header
	uint16_t	e_phnum; 					// count of program headers
	uint16_t	e_shentsize;				// size of single section header
	uint16_t	e_shnum; 					// count of section headers
	uint16_t	e_shstrndx;					// index of name's section in the table
	t_elf_section_table		*section_tables;
	t_elf_program_header	*program_headers;
};

struct s_elf_section_table {
	uint32_t	sh_name_offset;
	uint32_t	sh_type;
	uint64_t	sh_flags;
	uint64_t	sh_address;
	uint64_t	sh_offset;
	uint64_t	sh_size;
	uint32_t	sh_link;
	uint32_t	sh_info;
	uint64_t	sh_addralign;
	uint64_t	sh_entsize;
	char		*sh_name;
};

struct s_elf_program_header
{
	uint32_t	p_type;
	uint32_t	p_flags;
	uint64_t	p_offset;
	uint64_t	p_vaddr;
	uint64_t	p_paddr;
	uint64_t	p_filesz;
	uint64_t	p_memsz;
	uint64_t	p_align;
};


/**
 * Lists
 */

static const char *g_elf_section_table_type[] = {
	"NULL",
	"PROGBITS",
	"SYMTAB",
	"STRTAB",
	"RELA",
	"HASH",
	"DYNAMIC",
	"NOTE",
	"NOBITS",
	"REL",
	"SHLIB",
	"DYNSYM",
	"INIT_ARRAY",
	"FINI_ARRAY",
	"PREINIT_ARRAY",
	"GROUP",
	"SYMTAB_SHNDX",
	"NUM"
};

static const char *g_elf_osabi_name[] = {
	"UNIX - System V",
	"HP-UX",
	"NetBSD",
	"Linux",
	"GNU Hurd",
	"Solaris",
	"AIX (Monterey)",
	"IRIX",
	"FreeBSD",
	"Tru64",
	"Novell Modesto",
	"OpenBSD",
	"OpenVMS",
	"NonStop Kernel",
	"AROS",
	"FenixOS",
	"Nuxi CloudABI",
	"Stratus Technologies OpenVOS"
};

static const char *g_elf_program_header_type[] = {
	"NULL",
	"LOAD",
	"DYNAMIC",
	"INTERP",
	"NOTE",
	"SHLIB",
	"PHDR",
	"TLS",
	"NUM",
	"LOOS",
	"GNU_EH_FRAME",
	"GNU_STACK",
	"GNU_RELRO",
	"LOSUNW",
	"SUNWBSS",
	"SUNWSTACK",
	"HIOS",
	"LOPROC",
	"HIPROC"
};

/**
 * Function definitions
 */

t_elf_file		*new_elf_file(t_binary_reader *reader);
void			delete_elf_file(t_elf_file *file_format);

#define PELF_ALL		0x00
#define PELF_HEADER		0x01
#define PELF_SECTION	0x02

void			print_elf_file(t_elf_file *elf_file, int level);

int				packer(t_elf_file *old_elf_file, t_elf_file *new_elf_file, t_binary_reader *reader);

/**
 * Insertion
 */

void	elf_insert_section(t_elf_file *elf);

/* payload */

/**
 * On MacOS the symbol name must not be prefixed with an underscore when 
 * using extern symbole.
 */
#ifndef __APPLE__
#define CDECL_NORM(x) _ ## x
#else
#define CDECL_NORM(x) x
#endif /* __APPLE__ */

extern uint8_t	CDECL_NORM(payload_64);
extern uint64_t	CDECL_NORM(payload_size_64);

#define payload_64 CDECL_NORM(payload_64)
#define payload_size_64 CDECL_NORM(payload_size_64)

#endif /* WOODY_H */