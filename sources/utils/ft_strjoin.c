/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 21:23:49 by mgama             #+#    #+#             */
/*   Updated: 2023/12/05 14:52:03 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static char	*ft_strcpy(char *dest, char *src)
{
	int	index;

	index = 0;
	while (src[index] != '\0')
	{
		dest[index] = src[index];
		index++;
	}
	dest[index] = '\0';
	return (dest);
}

static int	ft_compute_final_length(char **strings, int size, int sep_length)
{
	int	final_length;
	int	i;

	final_length = 0;
	i = -1;
	while (++i < size)
	{
		final_length += ft_strlen(strings[i]);
		if (i < size - 1)
			final_length += sep_length;
	}
	return (final_length);
}

char	*ft_strjoin_arr(int size, char **strs, char *sep)
{
	int		full_length;
	int		i;
	char	*string;
	char	*tmp;

	if (!size)
		return ((char *)ft_calloc(1, sizeof(char)));
	full_length = ft_compute_final_length(strs, size, ft_strlen(sep));
	string = (char *)malloc((full_length + 1) * sizeof(char));
	if (!string)
		return (NULL);
	tmp = string;
	i = -1;
	while (++i < size)
	{
		ft_strcpy(tmp, strs[i]);
		tmp += ft_strlen(strs[i]);
		if (i < size - 1)
		{
			ft_strcpy(tmp, sep);
			tmp += ft_strlen(sep);
		}
	}
	*tmp = '\0';
	return (string);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1)
		s1 = (char *)ft_calloc(1, sizeof(char));
	if (!s1)
		return (NULL);
	if (!s2)
		return (free(s1), NULL);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	str = malloc(
			sizeof(char) * (i + j + 1));
	if (!str)
		return (free(s1), NULL);
	ft_memcpy(str, s1, i);
	ft_memcpy(str + i, s2, j);
	ft_memset(str + i + j, '\0', sizeof(char));
	free(s1);
	return (str);
}
