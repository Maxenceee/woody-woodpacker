/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pcolors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 16:09:35 by mgama             #+#    #+#             */
/*   Updated: 2024/02/18 12:08:56 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PCOLORS_H
# define PCOLORS_H

/*
 *	-- Header Color
 */

# define HEADER		"\x1b[1;38;5;216m"

/*
 *	-- Reset Colors
 */

# define RESET		"\033[0m"

/*
 *	-- Presets
 */

# define CBOLD		"\033[1m"
# define CDARK		"\033[2m"
# define CITALIC	"\033[3m"
# define CUNDERLINE	"\033[4m"

/*
 *	-- Defaults
 */

# define RED		"\033[0;31m"
# define GREEN		"\033[0;32m"
# define YELLOW		"\033[0;33m"
# define BLUE		"\033[0;34m"
# define PINK		"\033[0;35m"
# define CYAN		"\033[0;36m"
# define GREY		"\033[0;90m"
# define PURPLE		"\x1b[0;38;5;92m"

/*
 *	-- Bold
 */

# define B_RED		"\033[1;31m"
# define B_GREEN	"\033[1;32m"
# define B_YELLOW	"\033[1;33m"
# define B_ORANGE	"\x1b[1;38;5;202m"
# define B_BLUE		"\033[1;34m"
# define B_PINK		"\033[1;35m"
# define B_CYAN		"\033[1;36m"
# define B_GREY		"\033[1;90m"
# define B_PURPLE	"\x1b[1;38;5;92m"

/*
 *	-- Dark
 */

# define D_RED		"\033[2;31m"
# define D_GREEN	"\033[2;32m"
# define D_YELLOW	"\033[2;33m"
# define D_BLUE		"\033[2;34m"
# define D_PINK		"\033[2;35m"
# define D_CYAN		"\033[2;36m"
# define D_GREY		"\033[2;90m"
# define D_PURPLE	"\x1b[2;38;5;92m"

/*
 *	-- Italic
 */

# define I_RED		"\033[3;31m"
# define I_GREEN	"\033[3;32m"
# define I_YELLOW	"\033[3;33m"
# define I_BLUE		"\033[3;34m"
# define I_PINK		"\033[3;35m"
# define I_CYAN		"\033[3;36m"
# define I_GREY		"\033[3;90m"
# define I_PURPLE	"\x1b[3;38;5;92m"

/*
 *	-- Underline
 */

# define U_WHITE	"\033[4;1m"
# define U_RED		"\033[4;31m"
# define U_GREEN	"\033[4;32m"
# define U_YELLOW	"\033[4;33m"
# define U_BLUE		"\033[4;34m"
# define U_PINK		"\033[4;35m"
# define U_CYAN		"\033[4;36m"
# define U_GREY		"\033[4;90m"
# define U_PURPLE	"\x1b[4;38;5;92m"

/*
 *	-- Misc
 */

# define NL		"\n"
# define TAB	"\t"
# define DTAB	"\t\t"
# define TTAB	"\t\t\t"
# define QTAB	"\t\t\t\t"

#endif /* PCOLORS_H */
