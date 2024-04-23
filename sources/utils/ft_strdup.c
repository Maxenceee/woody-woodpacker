/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:42:36 by mgama             #+#    #+#             */
/*   Updated: 2023/12/05 14:52:11 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strdup(const char *src)
{
	char	*str;
	int		i;

	if (!src)
		return (NULL);
	i = ft_strlen(src);
	str = malloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_memcpy(str, src, i);
	ft_memset(str + i, '\0', sizeof(char));
	return (str);
}
