/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_reader.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 20:06:54 by mgama             #+#    #+#             */
/*   Updated: 2024/04/24 17:13:09 by mgama            ###   ########.fr       */
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

typedef struct s_binary_reader	t_binary_reader;

enum e_endian
{
	READER_BIG_ENDIAN		= 0X00,
	READER_LITTLE_ENDIAN	= 0X01
};

struct s_binary_reader
{
	uint32_t			_pos;
	unsigned char		*data;
	uint32_t			size;
	int					endian;

	uint32_t			((*seek)(t_binary_reader *, uint32_t));
	uint32_t			(*tell)(t_binary_reader *);

	uint8_t				(*get_uint8)(t_binary_reader *);
	uint16_t			(*get_uint16)(t_binary_reader *);
	uint32_t			(*get_uint32)(t_binary_reader *);
	uint64_t			(*get_uint64)(t_binary_reader *);

	int16_t				(*get_int16)(t_binary_reader *);
	int32_t				(*get_int32)(t_binary_reader *);
	int64_t				(*get_int64)(t_binary_reader *);

	int16_t				(*get_fword)(t_binary_reader *);
	int16_t				(*get_2dot14)(t_binary_reader *);
	int32_t				(*get_fixed)(t_binary_reader *);

	char				*(*get_string)(t_binary_reader *, uint16_t);
	char				*(*get_unicode_string)(t_binary_reader *, uint16_t);

	uint64_t			(*get_date)(t_binary_reader *);

	t_binary_reader		*(*slice)(t_binary_reader *, uint32_t, uint32_t);

	void				(*set_endian)(t_binary_reader *, int);
};

/* create new nibary reader */

t_binary_reader	*new_binary_reader(int fd);

/* init br methods */

void			init_binary_reader(t_binary_reader *reader);

/* delete binary reader */

void			delete_binary_reader(t_binary_reader *this);

/* read font file */

unsigned char	*ft_read_file(int fd, unsigned char *file,
					uint32_t *rsize);

/* join mem data */

unsigned char	*ft_memjoin(unsigned char *s1, unsigned char *s2,
					uint32_t size, uint32_t length);

/* binary reader methods */

uint32_t		br_seek(t_binary_reader *this, uint32_t pos);
uint32_t		br_tell(t_binary_reader *this);

uint8_t			br_get_uint8(t_binary_reader *this);
uint16_t		br_get_uint16(t_binary_reader *this);
uint32_t		br_get_uint32(t_binary_reader *this);
uint64_t		br_get_uint64(t_binary_reader *this);

int16_t			br_get_int16(t_binary_reader *this);
int32_t			br_get_int32(t_binary_reader *this);
int64_t			br_get_int64(t_binary_reader *this);

int16_t			br_get_fword(t_binary_reader *this);
int32_t			br_get_fixed(t_binary_reader *this);

char			*br_get_string(t_binary_reader *this, uint16_t length);
char			*br_get_unicode_string(t_binary_reader *this, uint16_t length);

uint64_t		br_get_date(t_binary_reader *this);

t_binary_reader	*br_slice(t_binary_reader *this, uint32_t start,
					uint32_t length);

void			br_set_endian(t_binary_reader *this, int endian);

#endif /* BINARY_READER_H */