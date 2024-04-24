/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   woody.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:09:20 by mgama             #+#    #+#             */
/*   Updated: 2024/04/24 15:46:13 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOODY_H
# define WOODY_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <fcntl.h>
# include  "reader/binary_reader.h"

#define WD_PREFIX "woody: "

#define WD_MAGIC 0x7F454C46

/*
 * Structures
 */

struct s_file_format {
	char		*e_ident_mag;				// magic number
	int			correcte_ident_mag;
	int			e_ident_class;				// 32 bits or 64 bits
	int 		e_ident_data;				// little of big endian
	char		*e_ident_data_type;
	int			e_type;						// object type
	char		*e_type_name;
	int			e_ident_osabi;				// operating system target
	void		*e_entry;					// address where the execution starts
	uint64_t	e_phoff;					// program headers' offset
	uint64_t	e_shoff;					// section headers' offset
	uint64_t	e_ehsize;					// elf header size
	uint16_t	e_phentsize; 				// size of a single program header
	uint16_t	e_phnum; 					// count of program headers
	uint16_t	e_shentsize;				// size of single section header
	uint16_t	e_shnum; 					// count of section headers
	uint16_t	e_shstrndx;					// index of name's section in the table
};

typedef struct s_file_format t_file_format;

/**
 * Function definitions
 */

t_file_format	*new_file_format(t_binary_reader *reader);
void			delete_file_format(t_file_format *file_format);

#endif /* WOODY_H */