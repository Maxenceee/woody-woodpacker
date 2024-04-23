/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   woody.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:09:20 by mgama             #+#    #+#             */
/*   Updated: 2024/04/23 17:03:46 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOODY_H
# define WOODY_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <fcntl.h>
# include  "../sources/reader/binary_reader.h"
typedef struct s_binary_reader	t_binary_reader;
#define WD_PREFIX "woody: "

#define WD_MAGIC 0xdeadbeef
struct s_file_Format {
	char	*filetype;
	int		correctfiletype;
	int		fileformat;
	char 	*endianness;
	int		endianness_Type;
	int		type;
	char	*type_Name;
	void	*entry;
	int32_t	offset_Header_Program;
	int32_t	offset_Header_Section;
};

typedef struct s_file_Format t_file_Format;


t_file_Format *new_file_format(t_binary_reader *reader);
void delete_file_format(t_file_Format *fileFormat);



#endif /* WOODY_H */