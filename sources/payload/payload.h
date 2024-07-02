/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   payload.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 22:36:41 by mgama             #+#    #+#             */
/*   Updated: 2024/07/02 22:38:05 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAYLOAD_H
# define PAYLOAD_H

const static unsigned char wd_playload_64[] = {
	0x48, 0x31, 0xc0, 0x48, 0x89, 0xc2, 0x48, 0x89, 0xc6, 0x48, 0x8d, 0x3d, 0x0d, 0x00, 0x00, 0x00,
	0x4c, 0x8d, 0x35, 0x0e, 0x00, 0x00, 0x00, 0x4c, 0x8d, 0x3d, 0x0f, 0x00, 0x00, 0x00, 0x4c, 0x8d,
	0x35, 0x10, 0x00, 0x00, 0x00, 0x4c, 0x8d, 0x3d, 0x11, 0x00, 0x00, 0x00, 0x4c, 0x8d, 0x35, 0x12,
	0x00, 0x00, 0x00, 0x4c, 0x8d, 0x3d, 0x13, 0x00, 0x00, 0x00, 0x4c, 0x8d, 0x35, 0x14, 0x00, 0x00,
	0x00, 0x4c, 0x8d, 0x3d, 0x15, 0x00, 0x00, 0x00, 0x4c, 0x8d, 0x35, 0x16, 0x00, 0x00, 0x00, 0x4c,
	0x8d, 0x3d, 0x17, 0x00, 0x00, 0x00, 0x4c, 0x8d, 0x35, 0x18, 0x00, 0x00, 0x00, 0x4c, 0x8d, 0x3d,
};

#endif /* PAYLOAD_H */