/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   woody.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:09:20 by mgama             #+#    #+#             */
/*   Updated: 2024/04/24 17:15:43 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOODY_H
# define WOODY_H

# include "reader/binary_reader.h"

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

struct s_elf_file {
	char		*e_ident_mag;				// magic number
	int			correcte_ident_mag;
	int			e_ident_class;				// 32 bits or 64 bits
	int 		e_ident_data;				// little of big endian
	char		*e_ident_data_type;
	int			e_type;						// object type
	char		*e_type_name;
	int			e_ident_osabi;				// operating system target
	uint64_t	e_entry;					// address where the execution starts
	uint64_t	e_phoff;					// program headers' offset
	uint64_t	e_shoff;					// section headers' offset
	uint64_t	e_ehsize;					// elf header size
	uint16_t	e_phentsize; 				// size of a single program header
	uint16_t	e_phnum; 					// count of program headers
	uint16_t	e_shentsize;				// size of single section header
	uint16_t	e_shnum; 					// count of section headers
	uint16_t	e_shstrndx;					// index of name's section in the table
	t_elf_section_table	*section_tables;
};

struct s_elf_section_table {
	uint32_t	sh_type;
	uint64_t	sh_flags;
	uint64_t	sh_address;
	uint64_t	sh_offset;
	uint64_t	sh_size;
};

/**
 * Function definitions
 */

t_elf_file		*new_elf_file(t_binary_reader *reader);
void			delete_elf_file(t_elf_file *file_format);
void			print_elf_file(t_elf_file *elf_file);

#endif /* WOODY_H */