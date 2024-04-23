/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:02:03 by mgama             #+#    #+#             */
/*   Updated: 2023/10/10 15:39:24 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	uint32_t	i;

	i = 0;
	while ((char)s1[i] == (char)s2[i] \
		&& (char)s1[i] != '\0' && (char)s2[i] != '\0')
	{
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_strncmp(const char *s1, const char *s2, uint32_t n)
{
	uint32_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((char)s1[i] == (char)s2[i] && i < n - 1 \
		&& (char)s1[i] != '\0' && (char)s2[i] != '\0')
	{
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_strnrcmp(const char *s1, const char *s2, uint32_t n)
{
	uint32_t	i;

	i = ft_max(ft_strlen(s1), ft_strlen(s2)) - 1;
	while (n > 0 && i > 0 && (char)s1[i] == (char)s2[n - 1])
	{
		i--;
		n--;
		if (n == 0)
			return (0);
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[n]);
}

int	ft_extension(char *str, char *end)
{
	int	len;
	int	count;

	len = ft_strlen(str) - 1;
	count = ft_strlen(end) - 1;
	if (len == count)
		return (0);
	while ((str[len--] == end[count]) && ((count > 0) && (len > 0)))
		count--;
	if (count == 0)
		return (1);
	return (0);
}
