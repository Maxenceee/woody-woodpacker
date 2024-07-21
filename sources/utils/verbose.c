/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 21:42:23 by mgama             #+#    #+#             */
/*   Updated: 2024/07/21 05:16:26 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdarg.h>

int	verbose_mode = VERBOSE_OFF;

void ft_putchar(char c)
{
	write(STDOUT_FILENO, &c, 1);
}

void ft_putstr_fd(char *s, int fd)
{
	size_t c;

	if (!s)
		s = "(null)";
	c = ft_strlen(s);
	write(fd, s, c);
}

void ft_putnbr_base(uint32_t nbr, int capitals, int baselen)
{
	if (nbr >= baselen)
	{
		ft_putnbr_base(nbr / baselen, capitals, baselen);
		ft_putnbr_base(nbr % baselen, capitals, baselen);
	}
	else
		ft_putchar(DIGITS[nbr + capitals]);
}

void ft_putnbr(int nb)
{
	if (nb == -2147483648)
		return ((void)ft_putstr_fd("-2147483648", STDOUT_FILENO));
	if (nb < 0)
	{
		ft_putchar('-');
		nb = -nb;
	}
	ft_putnbr_base(nb, 0, 10);
}

void ft_puthex_p(unsigned long int n)
{
	if (!n)
		return ((void)ft_putstr_fd("(nil)", STDOUT_FILENO));
	ft_putstr_fd("0x", STDOUT_FILENO);
	ft_putnbr_base(n, 0, 16);
}

void ft_switch_types(const char *fmt, va_list *argp, int hex)
{
	switch (*fmt)
	{
	case '%':
		ft_putchar('%');
		break;
	case 'c':
		ft_putchar(va_arg(*argp, long));
		break;
	case 's':
		ft_putstr_fd(va_arg(*argp, char *), STDOUT_FILENO);
		break;
	case 'd':
	case 'i':
		ft_putstr_fd(B_YELLOW, STDOUT_FILENO);
		ft_putnbr(va_arg(*argp, long));
		ft_putstr_fd(RESET, STDOUT_FILENO);
		break;
	case 'u':
		ft_putstr_fd(B_YELLOW, STDOUT_FILENO);
		ft_putnbr_base(va_arg(*argp, unsigned long), 0, 10);
		ft_putstr_fd(RESET, STDOUT_FILENO);
		break;
	case 'x':
		ft_putstr_fd(B_PINK, STDOUT_FILENO);
		if (hex)
			ft_putstr_fd("0x", STDOUT_FILENO);
		ft_putnbr_base(va_arg(*argp, uint32_t), 0, 16);
		ft_putstr_fd(RESET, STDOUT_FILENO);
		break;
	case 'X':
		ft_putstr_fd(B_PINK, STDOUT_FILENO);
		if (hex)
			ft_putstr_fd("0x", STDOUT_FILENO);
		ft_putnbr_base(va_arg(*argp, uint32_t), 16, 16);
		ft_putstr_fd(RESET, STDOUT_FILENO);
		break;
	case 'p':
		ft_putstr_fd(B_PINK, STDOUT_FILENO);
		ft_puthex_p(va_arg(*argp, unsigned long int));
		ft_putstr_fd(RESET, STDOUT_FILENO);
		break;
	}
}

void print_type(const char *fmt, va_list *argp)
{
	size_t i = 0;
	int	hex = 0;
	while (fmt[i] != '\0')
	{
		if (fmt[i] != '%')
		{
			ft_putchar(fmt[i++]);
			continue;
		}
		i++;
		if (fmt[i] == '#')
		{
			hex = 1;
			i++;
		}
		ft_switch_types(fmt + i, argp, hex);
		hex = 0;
		i++;
	}
}

void ft_verbose(const char *fmt, ...)
{
	if (verbose_mode == VERBOSE_OFF)
		return ;

	va_list listp;

	va_start(listp, fmt);
	print_type(fmt, &listp);
	va_end(listp);
}
