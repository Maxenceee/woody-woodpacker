/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 19:28:38 by mgama             #+#    #+#             */
/*   Updated: 2023/09/28 11:27:19 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	count_strings(const char *str, char *charset)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && check_separator(str[i], charset))
			i++;
		if (str[i] != '\0')
			count++;
		while (str[i] != '\0' && !check_separator(str[i], charset))
			i++;
	}
	return (count);
}

static int	ft_strlen_sep(const char *str, char *charset)
{
	int	i;

	i = 0;
	while (str[i] && !check_separator(str[i], charset))
		i++;
	return (i);
}

static char	*ft_word(const char *str, char *charset)
{
	int		len_word;
	int		i;
	char	*word;

	i = 0;
	len_word = ft_strlen_sep(str, charset);
	word = (char *)malloc(sizeof(char) * (len_word + 1));
	if (!word)
		return (0);
	while (i < len_word)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(const char *str, char *charset)
{
	char	**strings;
	int		i;

	if (str == NULL)
		return (NULL);
	i = 0;
	strings = (char **)malloc(sizeof(char *)
			* (count_strings(str, charset) + 1));
	if (!strings)
		return (0);
	while (*str != '\0')
	{
		while (*str != '\0' && check_separator(*str, charset))
			str++;
		if (*str != '\0')
		{
			strings[i] = ft_word(str, charset);
			if (strings[i++] == 0)
				return (free_tab(strings));
		}
		while (*str && !check_separator(*str, charset))
			str++;
	}
	strings[i] = 0;
	return (strings);
}
