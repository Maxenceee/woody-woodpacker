/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 19:02:43 by mgama             #+#    #+#             */
/*   Updated: 2023/12/06 13:57:55 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <fcntl.h>

/* ft_bzero */

int		ft_error(const char *str);
int		ft_error_msg(const char *str, const char *msg);
int		ft_warning(const char *str);
int		ft_info(const char *str);

int		ft_atoi(const char *str);
int		ft_ctoi(const char str);
char	*ft_itoa(int n);

void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_calloc(size_t count, size_t size);

int		check_separator(char c, char *charset);

char	**free_tab(char **tab);
char	**ft_split(const char *str, char *charset);

int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, uint32_t n);
int		ft_strnrcmp(const char *s1, const char *s2, uint32_t n);

size_t	ft_strlen(const char *str);
int		ft_tablen(char **str);

int		ft_max(int a, int b);
int		ft_min(int a, int b);
float	ft_fmax(float a, float b);
float	ft_fmin(float a, float b);

char	*ft_strjoin_arr(int size, char **strs, char *sep);
char	*ft_strjoin(char *s1, char *s2);
void	*ft_ljoin(void *s1, void *s2,
			unsigned int size, unsigned int length);

char	*ft_strchr(char *s, int c);
char	*ft_strdup(const char *src);
char	*ft_strtrim(char const *s1, char const *set);

int		ft_strlcpy(char *dest, char *src, uint32_t size);
void	ft_replace(char *src, char to_rep, char set);
int		ft_extension(char *str, char *end);
int		ft_strmultichr(char *str, char *chrlst);

#endif /* UTILS_H */