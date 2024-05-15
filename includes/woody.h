/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   woody.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:09:20 by mgama             #+#    #+#             */
/*   Updated: 2024/05/15 14:07:48 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOODY_H
# define WOODY_H

# include "reader/binary_reader.h"
# include "AES/aes.h"

#define WD_PREFIX "woody: "

#define WD_MAGIC 0x7F454C46

enum e_class {
	WD_32BITS = 1,
	WD_64BITS = 2
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
void			print_elf_file(t_elf_file *elf_file);

int				packer(t_elf_file *old_elf_file, t_elf_file *new_elf_file, t_binary_reader *reader);

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