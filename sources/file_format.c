/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:11:26 by mbrement          #+#    #+#             */
/*   Updated: 2024/04/24 15:49:01 by mbrement         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

static void get_Type(t_binary_reader *reader, t_file_format *file_format)
{
	reader->seek(reader, 16);
	file_format->e_type = reader->get_uint8(reader);
	 switch(file_format->e_type) {
		case 0x00 :
			file_format->e_type_name = "ET_NONE";
			break;
		case 0x01 :
			file_format->e_type_name = "ET_REL";
			break;
		case 0x02 :
			file_format->e_type_name = "ET_EXEC";
			break;
		case 0x03 :
			file_format->e_type_name = "ET_DYN";
			break;
		case 0x04 :
			file_format->e_type_name = "ET_CORE";
			break;
		case 0xFE00 :
			file_format->e_type_name = "ET_LOOS";
			break;
		case 0xFEFF :
			file_format->e_type_name = "ET_HIOS";
			break;
		case 0xFF00 :
			file_format->e_type_name = "ET_LOPROC";
			break;
		case 0xFFFF :
			file_format->e_type_name = "ET_HIPROC";
            break;
        default:
			file_format->e_type_name = "Error";
    }
}

t_file_format *new_file_format(t_binary_reader *reader)
{
	t_file_format *file_format = ft_calloc(1, sizeof(t_file_format));
	if (file_format == NULL)
		return (ft_error(WD_PREFIX"Could not allocate memory.\n"), NULL);
	reader->seek(reader, 1);
	file_format->e_ident_mag = reader->get_string(reader, 3);
	file_format->e_ident_class = reader->get_uint8(reader) * 32;

	if (ft_strcmp(file_format->e_ident_mag, "ELF") == 0)
	{
		file_format->correcte_ident_mag = 1;
	}
	else
	{
		file_format->correcte_ident_mag = 0;
	}

	file_format->e_ident_data = reader->get_uint8(reader);
	file_format->e_ident_data_type = file_format->e_ident_data - 1 ? "big endian" : "little endian";
	if (file_format->e_ident_data == 1)
	{
		reader->set_endian(reader, READER_LITTLE_ENDIAN);
	}

	/**
	 * We check that the e_ident version is 1, if not the file is not valid
	 */
	if (reader->get_uint8(reader) != 1)
	{
		delete_file_format(file_format);
		return (ft_error(WD_PREFIX"Wrong version.\n"), NULL);
	}

	file_format->e_ident_osabi =  reader->get_uint8(reader);
	if (file_format->e_ident_osabi != 0x00 && file_format->e_ident_osabi != 0x03)
	{
		delete_file_format(file_format);
		return (ft_error(WD_PREFIX"Invlide ABI.\n"), NULL);
	}

	get_Type(reader ,file_format);
	reader->seek(reader, 0x18);
	if (file_format->e_ident_class == 32)
	{
		file_format->e_entry += reader->get_uint32(reader);
		file_format->e_shoff = reader->get_uint32(reader);
		file_format->e_phoff = reader->get_uint32(reader);
	}
	else
	{
		file_format->e_entry += reader->get_uint64(reader);
		file_format->e_shoff = reader->get_uint64(reader);
		file_format->e_phoff = reader->get_uint64(reader);
	}

	(void)reader->get_uint32(reader);
	file_format->e_ehsize = reader->get_uint16(reader);
	file_format->e_phentsize = reader->get_uint16(reader);
	file_format->e_phnum = reader->get_uint16(reader);
	file_format->e_shentsize = reader->get_uint16(reader);
	file_format->e_shnum = reader->get_uint16(reader);

	return (file_format);
}

void delete_file_format(t_file_format *file_format)
{
	free(file_format->e_ident_mag);
	free(file_format);
}

