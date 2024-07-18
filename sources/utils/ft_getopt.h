/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 21:59:51 by mgama             #+#    #+#             */
/*   Updated: 2024/07/18 22:09:00 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTPARSE_H
#define OPTPARSE_H

struct optparse {
    char **argv;
    int permute;
    int optind;
    int optopt;
    char *optarg;
    char errmsg[64];
    int subopt;
};

enum optparse_argtype {
    OPTPARSE_NONE,
    OPTPARSE_REQUIRED,
    OPTPARSE_OPTIONAL
};

struct optparse_long {
    const char *longname;
    int shortname;
    enum optparse_argtype argtype;
};

/**
 * Initializes the parser state.
 */
void optparse_init(struct optparse *options, char **argv);

int optparse(struct optparse *options, const char *optstring);

int optparse_long(struct optparse *options,
                  const struct optparse_long *longopts,
                  int *longindex);

#define OPTPARSE_MSG_INVALID "invalid option"
#define OPTPARSE_MSG_MISSING "option requires an argument"
#define OPTPARSE_MSG_TOOMANY "option takes no arguments"

#endif /* OPTPARSE_H */