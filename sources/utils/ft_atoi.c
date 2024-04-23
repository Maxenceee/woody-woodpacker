/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:00:52 by mgama             #+#    #+#             */
/*   Updated: 2023/09/26 17:34:25 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_ctoi(const char str)
{
	unsigned long int	nbr;

	nbr = 0;
	if ((char)str == '-')
		return (-1);
	if ((char)str >= '0' && (char)str <= '9')
		nbr = nbr * 10 + ((char)str - '0');
	return (nbr);
}

int	ft_atoi(const char *str)
{
	int					i;
	unsigned long int	nbr;
	int					sign;

	i = 0;
	nbr = 0;
	sign = 0;
	if (!str)
		return (0);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if ((char)str[i] == '-' || (char)str[i] == '+')
		if ((char)str[i++] == '-')
			sign++;
	while ((char)str[i] >= '0' && (char)str[i] <= '9')
		nbr = nbr * 10 + ((char)str[i++] - '0');
	if (sign % 2 == 1)
		return (nbr * -1);
	return (nbr);
}
