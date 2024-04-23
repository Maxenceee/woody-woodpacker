/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minmax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 13:36:24 by mgama             #+#    #+#             */
/*   Updated: 2023/10/23 20:05:50 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_max(int a, int b)
{
	if (a < b)
		return (b);
	return (a);
}

int	ft_min(int a, int b)
{
	if (a > b)
		return (b);
	return (a);
}

float	ft_fmax(float a, float b)
{
	if (a < b)
		return (b);
	return (a);
}

float	ft_fmin(float a, float b)
{
	if (a > b)
		return (b);
	return (a);
}
