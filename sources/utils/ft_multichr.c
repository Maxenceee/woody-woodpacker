/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multichr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 15:15:06 by mgama             #+#    #+#             */
/*   Updated: 2023/09/26 17:34:07 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strchr(char *s, int c)
{
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}

int	ft_strmultichr(char *str, char *chrlst)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = NULL;
	if (!str)
		return (1);
	if ((str == NULL && chrlst == NULL) || ft_strlen(str) == 0)
		return (0);
	while (str[i])
	{
		ptr = ft_strchr(chrlst, str[i]);
		if (!ptr)
			return (0);
		i++;
	}
	return (1);
}
