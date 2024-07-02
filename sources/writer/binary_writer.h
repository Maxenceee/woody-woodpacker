/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_writer.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 20:06:54 by mgama             #+#    #+#             */
/*   Updated: 2024/07/02 19:14:57 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_WRITER_H
# define BINARY_WRITER_H

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

enum e_endian_writer
{
	WRITER_BIG_ENDIAN		= 0X00,
	WRITER_LITTLE_ENDIAN	= 0X01
};

struct s_binary_writer
{
	uint64_t			_pos;
	unsigned char		*data;
	uint64_t			size;
	int					endian;

	uint64_t			(*seek)(t_binary_writer *, uint64_t);
	uint64_t			(*tell)(t_binary_writer *);

	void				(*set_uint8)(t_binary_writer *, uint8_t);
	void				(*set_uint16)(t_binary_writer *, uint16_t);
	void				(*set_uint32)(t_binary_writer *, uint32_t);
	void				(*set_uint64)(t_binary_writer *, uint64_t);

	void				(*set_string)(t_binary_writer *, const char *);

	void				(*set_bytes)(t_binary_writer *, uint8_t *, uint32_t);
	// int					(*insert_section)(t_binary_writer *, ...);

	void				(*set_endian)(t_binary_writer *, int);
	void				(*set_padding)(t_binary_writer *, uint32_t);

	int					(*write_file)(t_binary_writer *, const char *);
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

uint64_t		bw_seek(t_binary_writer *this, uint64_t pos);
uint64_t		bw_tell(t_binary_writer *this);

void			bw_set_uint8(t_binary_writer *this, uint8_t value);
void			bw_set_uint16(t_binary_writer *this, uint16_t value);
void			bw_set_uint32(t_binary_writer *this, uint32_t value);
void			bw_set_uint64(t_binary_writer *this, uint64_t value);

void			bw_set_string(t_binary_writer *this, const char *string);

void			bw_set_bytes(t_binary_writer *this, uint8_t *data, uint32_t length);

void			bw_set_endian(t_binary_writer *this, int endian);
void			bw_set_padding(t_binary_writer *this, uint32_t padsize);

int				bw_write_file(t_binary_writer *this, const char *fname);

#endif /* BINARY_WRITER_H */