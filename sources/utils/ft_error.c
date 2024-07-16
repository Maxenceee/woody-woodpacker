/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 13:32:31 by mgama             #+#    #+#             */
/*   Updated: 2024/07/16 14:11:35 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "pcolors.h"
#include "woody.h"

int	ft_error(const char *str)
{
	return (dprintf(STDOUT_FILENO, "%s%s%s%s\n", RED, WD_PREFIX, str, RESET));
}

int	ft_error_msg(const char *str, const char *msg)
{
	return (dprintf(STDOUT_FILENO, "%s%s: %s: %s%s\n", RED, WD_PREFIX, str, msg, RESET));
}

int	ft_warning(const char *str)
{
	return (dprintf(STDOUT_FILENO, "%s%s: %s%s\n", B_YELLOW, WD_PREFIX, str, RESET));
}

int	ft_info(const char *str)
{
	return (printf("%s%s: %s%s", B_YELLOW, WD_PREFIX, str, RESET));
}
