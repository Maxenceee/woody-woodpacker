/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   woody.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:09:20 by mgama             #+#    #+#             */
/*   Updated: 2024/07/23 23:51:12 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOODY_H
# define WOODY_H

#if !defined(WD_32BITS_EXEC) && !defined(WD_64BITS_EXEC)
# define WD_64BITS_EXEC 
#endif /* WD_32BITS_EXEC */

#include <fcntl.h>
#include "reader/binary_reader.h"
#include "AES/aes.h"
#include "elf.h"
#include "payload/payload.h"

#define WD_VERSION "3.0"
#define WD_AUTHOR "mgama and mbrement"

#define WD_PREFIX "woody"
#ifndef WD_OUTPUT_FILE
#define WD_OUTPUT_FILE "woody"
#endif /* WD_OUTPUT_FILE */

#define WD_MAGIC 0x7F454C46

/**
 * Options
 */

#define F_KEY		0x01
#define F_HEADER	0x02
#define F_PROG		0x04
#define F_SECTION	0x08
#define F_SYM		0x10
#define F_DATA		0x20
#define F_UDSYM		0x40
#define F_NOOUTPUT	0x80


enum
{
	WD_32BITS = 1,
	WD_64BITS = 2
};

/*
 * Structures
 */

typedef union
{
    struct
    {
        uint32_t ei_magic;       // magic number
        uint8_t  ei_class;       // 32 bits or 64 bits
        uint8_t  ei_data;        // little or big endian
        uint8_t  ei_version;     // elf version
        uint8_t  ei_osabi;       // operating system target
        uint8_t  ei_abi_version; // abi version
        char     ei_pad[7];      // Reserved padding bytes
    };
    uint8_t raw[16];
} t_elf_ident;

typedef struct
{
	t_elf_ident	e_ident;
	uint16_t	e_type;						// object type
	uint16_t	e_machine;					// machine type
	uint32_t	e_version;					// object version
#ifdef WD_32BITS_EXEC
	uint32_t	e_entry;					// address where the execution starts
	uint32_t	e_phoff;					// program headers' offset
	uint32_t	e_shoff;					// section headers' offset
#else
	uint64_t	e_entry;					// address where the execution starts
	uint64_t	e_phoff;					// program headers' offset
	uint64_t	e_shoff;					// section headers' offset
#endif /* WD_32BITS_EXEC */
	uint32_t	e_flags;					// architecture-specific flags
	uint16_t	e_ehsize;					// elf header size
	uint16_t	e_phentsize; 				// size of a single program header
	uint16_t	e_phnum; 					// count of program headers
	uint16_t	e_shentsize;				// size of single section header
	uint16_t	e_shnum; 					// count of section headers
	uint16_t	e_shstrndx;					// index of name's section in the table
	t_elf_program_header	*program_headers;
	t_elf_section			*section_tables;
}	t_elf_file;

#define WD_ELF_HEADER_SIZE (sizeof(t_elf_file) - sizeof(t_elf_program_header *) - sizeof(t_elf_section *))
#define WD_ELF_PROGRAM_HEADER_SIZE sizeof(t_elf_program_header)
#define WD_ELF_SECTION_HEADER_SIZE (sizeof(t_elf_section) - sizeof(char *) - sizeof(uint8_t *))

// Check endianness and swap bytes if needed
#define MAGIC(x, e)	(e == LITTLE_ENDIAN ? x : ((x >> 24) & 0xff) | ((x >> 8) & 0xff00) | ((x << 8) & 0xff0000) | ((x << 24) & 0xff000000))

/**
 * key
 */

#define WD_AES_KEY_SIZE 16
extern uint8_t	key_aes[WD_AES_KEY_SIZE];

/**
 * packer
 */

#define WB_SECTION_NAME ".i'm a teapot"

typedef struct
{
	uint64_t	loader_offset;
	uint8_t		*payload;
	uint64_t	payload_size;
	uint64_t	new_section_size;
}	t_packer;

/**
 * Function definitions
 */

t_elf_file		*new_elf_file(t_binary_reader *reader);
void			delete_elf_file(t_elf_file *file_format);

#define PELF_ALL		0x01
#define PELF_HEADER		0x02
#define PELF_PROG		0x04
#define PELF_SECTION	0x08
#define PELF_SYM		0x10
#define PELF_DATA		0x20
#define PELF_ERROR		0x80

void			print_elf_file(t_elf_file *elf_file, int level);

int				packer(t_elf_file *elf);

/**
 * Insertion
 */

int	elf_insert_section(t_elf_file *elf, int opt);
t_elf_section	*get_text_section(t_elf_file *elf);

#endif /* WOODY_H */