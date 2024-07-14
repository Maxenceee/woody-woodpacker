/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   payload.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 22:36:41 by mgama             #+#    #+#             */
/*   Updated: 2024/07/14 17:43:25 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAYLOAD_H
# define PAYLOAD_H

#define WB_PAYLOAD_SIZE (sizeof(wd_playload_64))

#define WD_PAYLOAD_OFF_KEY (24 + 64)
#define WD_PAYLOAD_RETURN_ADDR (24 + 64 + 4)

static const unsigned char wd_playload_64[] = {
	// 0x50, 0x57, 0x56, 0x54, 0x52, 0x51, 0x53, 0xe8, 0x16, 0x00, 0x00, 0x00, 0x83, 0xea, 0xfe, 0x89,
	// 0xd1, 0xba, 0x0f, 0x00, 0x00, 0x00, 0xbb, 0x01, 0x00, 0x00, 0x00, 0xb8, 0x04, 0x00, 0x00, 0x00,
	// 0x0f, 0x05, 0xe8, 0x00, 0x00, 0x00, 0x00, 0x5a, 0xc3, 0x2e, 0x2e, 0x2e, 0x2e, 0x57, 0x4f, 0x4f,
	// 0x44, 0x59, 0x2e, 0x2e, 0x2e, 0x2e, 0x0a, 0x00, 0x48, 0x81, 0xc4, 0xa0, 0x00, 0x00, 0x00, 0x5b,
	// 0x59, 0x5a, 0x5c, 0x5e, 0x5f, 0x58, 0xe9, 0xfb, 0xff, 0xff, 0xff, 0x61, 0x61, 0x61, 0x61, 0x61,
	// 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61,
	// 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61,
	// 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61,
	// 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb,
	// 0xbb, 0xbb, 0xbb, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd,
	// 0xdd, 0xdd, 0xdd,

	0x50, 0x52, 0x56, 0x57, 0xeb, 0x0f, 0x2e, 0x2e, 0x2e, 0x2e, 0x57, 0x4f, 0x4f, 0x44, 0x59, 0x2e,
	0x2e, 0x2e, 0x2e, 0x0a, 0x00, 0xb8, 0x01, 0x00, 0x00, 0x00, 0xbf, 0x01, 0x00, 0x00, 0x00, 0x48,
	0x8d, 0x35, 0xe0, 0xff, 0xff, 0xff, 0xba, 0x0f, 0x00, 0x00, 0x00, 0x0f, 0x05, 0x5f, 0x5e, 0x5a,
	0x58, 0xe8, 0x00, 0x03, 0x02, 0x01, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61,
	0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61,
	0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61,
	0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61,
	0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xcc, 0xcc,
	0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd

	// 0x9c, 0x50, 0x52, 0x56, 0x57, 0xeb, 0x0f, 0x2e, 0x2e, 0x2e, 0x2e, 0x57, 0x4f, 0x4f, 0x44, 0x59,
	// 0x2e, 0x2e, 0x2e, 0x2e, 0x0a, 0x00, 0xb8, 0x01, 0x00, 0x00, 0x00, 0xbf, 0x01, 0x00, 0x00, 0x00,
	// 0x48, 0x8d, 0x35, 0xe0, 0xff, 0xff, 0xff, 0xba, 0x0f, 0x00, 0x00, 0x00, 0x0f, 0x05, 0x5f, 0x5e,
	// 0x5a, 0x58, 0x9d, 0xe9, 0x00, 0x03, 0x02, 0x01, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61,
	// 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61,
	// 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61,
	// 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61,
	// 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0x61, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb,
	// 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd,
};

#endif /* PAYLOAD_H */