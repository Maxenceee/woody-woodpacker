/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:11:56 by mgama             #+#    #+#             */
/*   Updated: 2024/07/17 22:12:18 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char *optarg = NULL; 
int optind = 1;

int ft_getopt(int argc, char * const argv[], const char *optstring)
{
	static int optpos = 1;

	if (optind >= argc || argv[optind][0] != '-') {
		return (-1);
	}

	if (argv[optind][0] == '-' && argv[optind][1] == '-') {
		optind++;
		return (-1);
	}

	if (optpos == 1 && strchr(optstring, argv[optind][1]) && strchr(optstring, argv[optind][1])[1] == ':') {
		if (argv[optind][2] != '\0') {
			optarg = &argv[optind][2];
			optind++;
			return (argv[optind - 1][1]);
		} else if (optind + 1 < argc) {
			optarg = argv[optind + 1];
			optind += 2;
			return (argv[optind - 2][1]);
		} else {
			optind++;
			return ('?');
		}
	}

	if (argv[optind][optpos] == '\0') {
		optind++;
		optpos = 1;
		return (ft_getopt(argc, argv, optstring));
	}

	char optchar = argv[optind][optpos];
	char *optdecl = strchr(optstring, optchar);

	if (optdecl == NULL) {
		optpos++;
		if (argv[optind][optpos] == '\0') {
			optind++;
			optpos = 1;
		}
		return ('?');
	}

	if (optdecl[1] == ':') {
		optind++;
		optpos = 1;
		return ('?');
	} else {
		optpos++;
		if (argv[optind][optpos] == '\0') {
			optind++;
			optpos = 1;
		}
		return (optchar);
	}
}
