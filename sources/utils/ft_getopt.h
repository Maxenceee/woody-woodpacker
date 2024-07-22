/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 21:59:51 by mgama             #+#    #+#             */
/*   Updated: 2024/07/22 17:57:40 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTPARSE_H
#define OPTPARSE_H

struct getopt_s
{
    char **argv;
    int permute;
    int optind;
    int optopt;
    char *optarg;
    char errmsg[64];
    int subopt;
};

enum getopt_argtype_e {
    OPTPARSE_NONE,
    OPTPARSE_REQUIRED,
    OPTPARSE_OPTIONAL
};

struct getopt_list_s
{
    const char *longname;
    int shortname;
    enum getopt_argtype_e argtype;
};

/**
 * Initializes the parser state.
 */
void ft_getopt_init(struct getopt_s *options, char **argv);

int ft_getopt(struct getopt_s *options,
                  const struct getopt_list_s *longopts,
                  int *longindex);

#define OPTPARSE_MSG_INVALID "invalid option"
#define OPTPARSE_MSG_MISSING "option requires an argument"
#define OPTPARSE_MSG_TOOMANY "option takes no arguments"

#endif /* OPTPARSE_H */