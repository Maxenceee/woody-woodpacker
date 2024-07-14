/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   woody.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:09:20 by mgama             #+#    #+#             */
/*   Updated: 2024/07/14 18:59:34 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOODY_H
# define WOODY_H

#include <fcntl.h>
#include <string.h>
#include "reader/binary_reader.h"
#include "AES/aes.h"
#include "elf.h"
#include "payload/payload.h"

#define WD_PREFIX "woody: "

#define WD_MAGIC 0x7F454C46

/**
 * Options
 */

#define F_KEY		0x01
#define F_HEADER	0x02
#define F_SECTION	0x04
#define F_DATA		0x08
#define F_ENCRYPT	0x10
#define F_DECRYPT	0x20
#define F_NOOUTPUT	0x80


enum e_class {
	WD_32BITS = 1,
	WD_64BITS = 2
};

/*
 * Structures
 */

typedef struct s_elf_file {
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

		uint8_t		raw[16];
	} e_ident;

	uint16_t	e_type;						// object type
	uint16_t	e_machine;					// machine type
	uint32_t	e_version;					// object version
	uint64_t	e_entry;					// address where the execution starts
	uint64_t	e_phoff;					// program headers' offset
	uint64_t	e_shoff;					// section headers' offset
	uint32_t	e_flags;					// architecture-specific flags
	uint16_t	e_ehsize;					// elf header size
	uint16_t	e_phentsize; 				// size of a single program header
	uint16_t	e_phnum; 					// count of program headers
	uint16_t	e_shentsize;				// size of single section header
	uint16_t	e_shnum; 					// count of section headers
	uint16_t	e_shstrndx;					// index of name's section in the table
	char		*e_type_name;
	t_elf_program_header	*program_headers;
	t_elf_section_table		*section_tables;
}	t_elf_file;

/**
 * key
 */

#define WD_AES_KEY_SIZE 64
extern uint8_t	key_aes[WD_AES_KEY_SIZE];

/**
 * packer
 */

#define WB_SECTION_NAME ".i'm a teapot"

typedef struct s_packer {
	uint64_t	loader_offset;
	uint8_t		*payload_64;
	uint64_t	payload_64_size;
	uint64_t	new_section_size;
}	t_packer;

/**
 * Function definitions
 */

t_elf_file		*new_elf_file(t_binary_reader *reader);
void			delete_elf_file(t_elf_file *file_format);

#define PELF_ALL		0x01
#define PELF_HEADER		0x02
#define PELF_SECTION	0x04
#define PELF_DATA		0x08

void			print_elf_file(t_elf_file *elf_file, int level);

int				packer(t_elf_file *elf, t_binary_reader *reader);

/**
 * Insertion
 */

int	elf_insert_section(t_elf_file *elf);

#endif /* WOODY_H */