/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:00:38 by mgama             #+#    #+#             */
/*   Updated: 2024/07/12 18:52:48 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELF_H
#define ELF_H

#include <stdint.h>

#define	PT_NULL		0		/* Program header table entry unused */
#define PT_LOAD		1		/* Loadable program segment */
#define PT_DYNAMIC	2		/* Dynamic linking information */
#define PT_INTERP	3		/* Program interpreter */
#define PT_NOTE		4		/* Auxiliary information */
#define PT_SHLIB	5		/* Reserved */
#define PT_PHDR		6		/* Entry for header table itself */
#define PT_TLS		7		/* Thread-local storage segment */
#define	PT_NUM		8		/* Number of defined types */
#define PT_LOOS		0x60000000	/* Start of OS-specific */
#define PT_GNU_EH_FRAME	0x6474e550	/* GCC .eh_frame_hdr segment */
#define PT_GNU_STACK	0x6474e551	/* Indicates stack executability */
#define PT_GNU_RELRO	0x6474e552	/* Read-only after relocation */
#define PT_LOSUNW	0x6ffffffa
#define PT_SUNWBSS	0x6ffffffa	/* Sun Specific segment */
#define PT_SUNWSTACK	0x6ffffffb	/* Stack segment */
#define PT_HISUNW	0x6fffffff
#define PT_HIOS		0x6fffffff	/* End of OS-specific */
#define PT_LOPROC	0x70000000	/* Start of processor-specific */
#define PT_HIPROC	0x7fffffff	/* End of processor-specific */

typedef struct s_elf_section_table {
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
	uint8_t		*data;
	char		*sh_name;
}	t_elf_section_table;

typedef struct s_elf_program_header
{
	uint32_t	p_type;
	uint32_t	p_flags;
	uint64_t	p_offset;
	uint64_t	p_vaddr;
	uint64_t	p_paddr;
	uint64_t	p_filesz;
	uint64_t	p_memsz;
	uint64_t	p_align;
}	t_elf_program_header;

#define SHT_NULL			0		/* Section header table entry unused */
#define SHT_PROGBITS		1		/* Program data */
#define SHT_SYMTAB			2		/* Symbol table */
#define SHT_STRTAB			3		/* String table */
#define SHT_RELA			4		/* Relocation entries with addends */
#define SHT_HASH			5		/* Symbol hash table */
#define SHT_DYNAMIC			6		/* Dynamic linking information */
#define SHT_NOTE			7		/* Notes */
#define SHT_NOBITS			8		/* Program space with no data (bss) */
#define SHT_REL				9		/* Relocation entries, no addends */
#define SHT_SHLIB			10		/* Reserved */
#define SHT_DYNSYM			11		/* Dynamic linker symbol table */
#define SHT_INIT_ARRAY		14		/* Array of constructors */
#define SHT_FINI_ARRAY		15		/* Array of destructors */
#define SHT_PREINIT_ARRAY	16		/* Array of pre-constructors */
#define SHT_GROUP			17		/* Section group */
#define SHT_SYMTAB_SHNDX	18		/* Extended section indeces */
#define	SHT_NUM				19		/* Number of defined types.  */
#define SHT_LOOS			0x60000000	/* Start OS-specific.  */
#define SHT_GNU_ATTRIBUTES	0x6ffffff5	/* Object attributes.  */
#define SHT_GNU_HASH		0x6ffffff6	/* GNU-style hash table.  */
#define SHT_GNU_LIBLIST		0x6ffffff7	/* Prelink library list */
#define SHT_CHECKSUM		0x6ffffff8	/* Checksum for DSO content.  */
#define SHT_LOSUNW			0x6ffffffa	/* Sun-specific low bound.  */
#define SHT_SUNW_move		0x6ffffffa
#define SHT_SUNW_COMDAT		0x6ffffffb
#define SHT_SUNW_syminfo	0x6ffffffc
#define SHT_GNU_verdef		0x6ffffffd	/* Version definition section.  */
#define SHT_GNU_verneed		0x6ffffffe	/* Version needs section.  */
#define SHT_GNU_versym		0x6fffffff	/* Version symbol table.  */
#define SHT_HISUNW			0x6fffffff	/* Sun-specific high bound.  */
#define SHT_HIOS			0x6fffffff	/* End OS-specific type */
#define SHT_LOPROC			0x70000000	/* Start of processor-specific */
#define SHT_HIPROC			0x7fffffff	/* End of processor-specific */
#define SHT_LOUSER			0x80000000	/* Start of application-specific */
#define SHT_HIUSER			0x8fffffff	/* End of application-specific */

/* Legal values for sh_flags (section flags).  */

#define SHF_WRITE				(1 << 0)	/* Writable */
#define SHF_ALLOC				(1 << 1)	/* Occupies memory during execution */
#define SHF_EXECINSTR			(1 << 2)	/* Executable */
#define SHF_MERGE				(1 << 4)	/* Might be merged */
#define SHF_STRINGS				(1 << 5)	/* Contains nul-terminated strings */
#define SHF_INFO_LINK			(1 << 6)	/* `sh_info' contains SHT index */
#define SHF_LINK_ORDER			(1 << 7)	/* Preserve order after combining */
#define SHF_OS_NONCONFORMING	(1 << 8)	/* Non-standard OS specific handling */

/* Legal values for p_flags (segment flags).  */

#define PF_X		(1 << 0)	/* Segment is executable */
#define PF_W		(1 << 1)	/* Segment is writable */
#define PF_R		(1 << 2)	/* Segment is readable */
#define PF_MASKOS	0x0ff00000	/* OS-specific */
#define PF_MASKPROC	0xf0000000	/* Processor-specific */

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

#endif /* ELF_H */