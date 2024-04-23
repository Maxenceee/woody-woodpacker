/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:11:26 by mbrement          #+#    #+#             */
/*   Updated: 2024/04/23 17:47:10 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

static void get_Type(t_binary_reader *reader, t_file_Format *fileFormat)
{
	reader->seek(reader, 16);
	fileFormat->type = reader->get_uint8(reader);
	 switch(fileFormat->type) {
		case 0x00 :
			fileFormat->type_Name = "ET_NONE";
			break;
		case 0x01 :
			fileFormat->type_Name = "ET_REL";
			break;
		case 0x02 :
			fileFormat->type_Name = "ET_EXEC";
			break;
		case 0x03 :
			fileFormat->type_Name = "ET_DYN";
			break;
		case 0x04 :
			fileFormat->type_Name = "ET_CORE";
			break;
		case 0xFE00 :
			fileFormat->type_Name = "ET_LOOS";
			break;
		case 0xFEFF :
			fileFormat->type_Name = "ET_HIOS";
			break;
		case 0xFF00 :
			fileFormat->type_Name = "ET_LOPROC";
			break;
		case 0xFFFF :
			fileFormat->type_Name = "ET_HIPROC";
            break;
        default:
			fileFormat->type_Name = "Error";
    }	
}

t_file_Format *new_file_format(t_binary_reader *reader)
{
	t_file_Format *fileFormat = ft_calloc(1, sizeof(t_file_Format));
	if (fileFormat == NULL)
		return (ft_error(WD_PREFIX"Could not allocate memory.\n"), NULL);
	reader->seek(reader, 1);
	fileFormat->filetype = reader->get_string(reader, 3);
	fileFormat->fileformat = (32 << reader->get_uint8(reader));
	if (ft_strcmp(fileFormat->filetype, "ELF") == 0)
		fileFormat->correctfiletype = 1;
	else
		fileFormat->correctfiletype = 0;
	fileFormat->endianness = reader->get_uint8(reader) - 1 ? "little endianness" : "big endianness";
	fileFormat->endianness_Type = reader->get_uint8(reader);
	get_Type(reader, fileFormat);
	fileFormat->entry = 0;
	reader->seek(reader, 0x18);
	if (fileFormat->fileformat / 32 == 1)
		fileFormat->entry += reader->get_uint32(reader);
	else
		fileFormat->entry += reader->get_uint64(reader);
	// unsure if it's right after
	fileFormat->offset_Header_Program = reader->get_uint32(reader);
	fileFormat->offset_Header_Section = reader->get_uint32(reader);
	return (fileFormat);
}

void delete_file_format(t_file_Format *fileFormat)
{
	free(fileFormat->filetype);
	free(fileFormat);
}
