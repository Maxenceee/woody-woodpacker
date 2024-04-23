/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 13:32:31 by mgama             #+#    #+#             */
/*   Updated: 2023/12/06 13:57:44 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "pcolors.h"

int	ft_error(const char *str)
{
	int	r;

	r = 0;
	r += write(2, B_RED, 8);
	r += write(2, str, ft_strlen(str));
	r += write(2, RESET, 4);
	return (r);
}

int	ft_error_msg(const char *str, const char *msg)
{
	int	r;

	r = 0;
	r += write(2, B_RED, 8);
	r += write(2, str, ft_strlen(str));
	r += write(2, ": ", 2);
	r += write(2, msg, ft_strlen(msg));
	r += write(2, "\n", 1);
	r += write(2, RESET, 4);
	return (r);
}

int	ft_warning(const char *str)
{
	int	r;

	r = 0;
	r += write(2, B_YELLOW, 8);
	r += write(2, str, ft_strlen(str));
	r += write(2, RESET, 4);
	return (r);
}

int	ft_info(const char *str)
{
	return (printf("%s%s%s", B_YELLOW, str, RESET));
}
