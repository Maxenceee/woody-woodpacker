/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:00:38 by mgama             #+#    #+#             */
/*   Updated: 2024/07/17 21:41:05 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELF_H
#define ELF_H

#include <stdint.h>

#define ET_NONE		0		/* No file type */
#define ET_REL		1		/* Relocatable file */
#define ET_EXEC		2		/* Executable file */
#define ET_DYN		3		/* Shared object file */
#define ET_CORE		4		/* Core file */
#define	ET_NUM		5		/* Number of defined types */
#define ET_LOOS		0xfe00	/* OS-specific range start */
#define ET_HIOS		0xfeff	/* OS-specific range end */
#define ET_LOPROC	0xff00	/* Processor-specific range start */
#define ET_HIPROC	0xffff	/* Processor-specific range end */

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
#define PT_GNU_PROPERTY	0x6474e553
#define PT_LOSUNW	0x6ffffffa
#define PT_SUNWBSS	0x6ffffffa	/* Sun Specific segment */
#define PT_SUNWSTACK	0x6ffffffb	/* Stack segment */
#define PT_HISUNW	0x6fffffff
#define PT_HIOS		0x6fffffff	/* End of OS-specific */
#define PT_LOPROC	0x70000000	/* Start of processor-specific */
#define PT_HIPROC	0x7fffffff	/* End of processor-specific */

typedef struct
{
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

typedef struct
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

typedef struct
{
	uint32_t	st_name;
	uint8_t		st_info;
	uint8_t		st_other;
	uint16_t	st_shndx;
	uint64_t	st_value;
	uint64_t	st_size;
}	t_elf_sym;

enum
{
	STB_LOCAL	= 0,
	STB_GLOBAL	= 1,
	STB_WEAK	= 2,
	STB_LOOS	= 10,
	STB_HIOS	= 12,
	STB_LOPROC	= 13,
	STB_HIPROC	= 15,
};
 
enum
{
	STT_NOTYPE	= 0,
	STT_OBJECT	= 1,
	STT_FUNC	= 2,
	STT_SECTION	= 3,
	STT_FILE	= 4,
	STT_LOOS	= 10,
	STT_HIOS	= 12,
	STT_LOPROC	= 13,
	STT_HIPROC	= 15,
};

#define ELF64_ST_BIND(i)    ((i)>>4)
 
#define ELF64_ST_TYPE(i)    ((i)&0xf)
 
#define ELF64_ST_INFO(b,t)  (((b)<<4)+((t)&0xf))

enum
{
	STV_DEFAULT		= 0,
	STV_INTERNAL	= 1,
	STV_HIDDEN		= 2,
	STV_PROTECTED	= 3,
};

#endif /* ELF_H */