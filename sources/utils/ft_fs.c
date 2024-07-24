/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:18:32 by mgama             #+#    #+#             */
/*   Updated: 2024/07/24 16:19:31 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int is_same_file(const char *file1, const char *file2)
{
	struct stat stat1, stat2;

	if (stat(file1, &stat1) != 0) {
		perror("stat");
		return 0;
	}

	if (stat(file2, &stat2) != 0) {
		perror("stat");
		return 0;
	}

	return (stat1.st_ino == stat2.st_ino) && (stat1.st_dev == stat2.st_dev);
}
