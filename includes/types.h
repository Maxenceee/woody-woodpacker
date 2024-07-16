/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:18:59 by mgama             #+#    #+#             */
/*   Updated: 2024/07/16 19:19:07 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

/**
 * On MacOS the symbol name must not be prefixed with an underscore when 
 * using extern symbole.
 */
#ifndef __APPLE__
#define CDECL_NORM(x) _ ## x
#else
#define CDECL_NORM(x) x
#endif /* __APPLE__ */

#endif /* TYPES_H */