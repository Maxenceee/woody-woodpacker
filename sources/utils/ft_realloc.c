/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:54:07 by mgama             #+#    #+#             */
/*   Updated: 2024/07/20 15:15:14 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void *ft_realloc(void *ptr, size_t size)
{
	void *new_ptr;

	new_ptr = malloc(size);
	if (new_ptr == NULL)
		return NULL;
	if (ptr)
	{
		ft_memcpy(new_ptr, ptr, size);
		free(ptr);
	}
	return new_ptr;
}