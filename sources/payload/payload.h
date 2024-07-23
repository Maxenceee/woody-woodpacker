/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   payload.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 22:36:41 by mgama             #+#    #+#             */
/*   Updated: 2024/07/23 23:53:55 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAYLOAD_H
# define PAYLOAD_H

#include "types.h"

#define payload_64 CDECL_NORM(payload_aes128_64)
#define payload_64_size CDECL_NORM(payload_aes128_64_size)

extern uint8_t	payload_64;
extern uint64_t	payload_64_size;

#define wd_playload &payload_64
#define WB_PAYLOAD_SIZE payload_64_size

#define WD_PAYLOAD_RETURN_ADDR (24 + 16 + 4) // 3 * sizeof(uint64_t) + sizeof(aes_key) + sizeof(int32_t)
#define WD_PAYLOAD_OFF_KEY (24 + 16) // 3 * sizeof(uint64_t) + sizeof(aes_key)
#define WD_PAYLOAD_OFF_DATA_ADDR (24) // 3 * sizeof(uint64_t) 
#define WD_PAYLOAD_OFF_DATA_START (16) // 2 * sizeof(uint64_t)
#define WD_PAYLOAD_OFF_DATA_SIZE (8) //  sizeof(uint64_t)

/**
 * INFO: Built-in example
 */

// #define WB_PAYLOAD_SIZE sizeof(wd_playload_64)
// static const unsigned char wd_playload_64[] = {
// 	0x50, 0x52, 0x56, 0x57, 0xeb, 0x0f, 0x2e, 0x2e, 0x2e, 0x2e, 0x57, 0x4f, 0x4f, 0x44, 0x59, 0x2e,
// 	0x2e, 0x2e, 0x2e, 0x0a, 0x00, 0xb8, 0x01, 0x00, 0x00, 0x00, 0xbf, 0x01, 0x00, 0x00, 0x00, 0x48,
// 	0x8d, 0x35, 0xe0, 0xff, 0xff, 0xff, 0xba, 0x0f, 0x00, 0x00, 0x00, 0x0f, 0x05, 0x5f, 0x5e, 0x5a,
// 	0x58, 0xe9, 0x00, 0x03, 0x02, 0x01, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61,
// 	0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61,
// 	0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61,
// 	0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61,
// 	0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xcc, 0xcc,
// 	0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd
// };

#endif /* PAYLOAD_H */