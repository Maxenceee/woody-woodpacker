/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_writer.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 20:06:54 by mgama             #+#    #+#             */
/*   Updated: 2024/06/28 21:54:23 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_READER_H
# define BINARY_READER_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <fcntl.h>
# include "utils/utils.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct s_binary_writer	t_binary_writer;

enum e_endian
{
	WRITER_BIG_ENDIAN		= 0X00,
	WRITER_LITTLE_ENDIAN	= 0X01
};

struct s_binary_writer
{
	uint32_t			_pos;
	unsigned char		*data;
	uint32_t			size;
	int					endian;

	uint32_t			((*seek)(t_binary_writer *, uint32_t));
	uint32_t			(*tell)(t_binary_writer *);

	void				(*set_uint8)(t_binary_writer *, uint8_t);
	void				(*set_uint16)(t_binary_writer *, uint16_t);
	void				(*set_uint32)(t_binary_writer *, uint32_t);
	void				(*set_uint64)(t_binary_writer *, uint64_t);

	void				(*set_int16)(t_binary_writer *, int16_t);
	void				(*set_int32)(t_binary_writer *, int32_t);
	void				(*set_int64)(t_binary_writer *, int64_t);

	void				(*set_string)(t_binary_writer *, char *, uint16_t);

	void				(*set_bytes)(t_binary_writer *, uint8_t *, uint32_t);
	// int					(*insert_section)(t_binary_writer *, ...);

	void				(*set_endian)(t_binary_writer *, int);
};

/* create new nibary reader */

t_binary_writer	*new_binary_writer(uint8_t *buffer, uint32_t size);

/* init bw methods */

void			init_binary_writer(t_binary_writer *reader);

/* delete binary reader */

void			delete_binary_writer(t_binary_writer *this);

/* read font file */

unsigned char	*ft_read_file(int fd, unsigned char *file,
					uint32_t *rsize);

/* join mem data */

unsigned char	*ft_memjoin(unsigned char *s1, unsigned char *s2,
					uint32_t size, uint32_t length);

/* binary reader methods */

uint32_t		bw_seek(t_binary_writer *this, uint32_t pos);
uint32_t		bw_tell(t_binary_writer *this);

void			bw_set_uint8(t_binary_writer *this, uint8_t value);
void			bw_set_uint16(t_binary_writer *this, uint16_t value);
void			bw_set_uint32(t_binary_writer *this, uint32_t value);
void			bw_set_uint64(t_binary_writer *this, uint64_t value);

void			bw_set_int16(t_binary_writer *this, int16_t value);
void			bw_set_int32(t_binary_writer *this, int32_t value);
void			bw_set_int64(t_binary_writer *this, int64_t value);

void			bw_set_string(t_binary_writer *this, char *string, uint16_t length);

void			bw_set_bytes(t_binary_writer *this, uint8_t *target, uint32_t length);

void			bw_set_endian(t_binary_writer *this, int endian);

#endif /* BINARY_READER_H */