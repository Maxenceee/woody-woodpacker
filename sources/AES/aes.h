/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aes.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 14:17:15 by mgama             #+#    #+#             */
/*   Updated: 2024/07/23 19:22:21 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AES_H
# define AES_H

#include "types.h"

/**
 * AES 256 bits
 */

#define AES_256_Key_Expansion CDECL_NORM(AES_256_Key_Expansion)
#define AES_CTR_encrypt CDECL_NORM(AES_CTR_encrypt)

void	AES_256_Key_Expansion(const unsigned char *userkey, unsigned char *key);
void	AES_CTR_encrypt(const unsigned char *in, unsigned char *out, const unsigned char ivec[8], const unsigned char nonce[4], unsigned long length, const unsigned char *key, int nr);

/**
 * AES 128 bits ecb
 */

#define aes_128_ecb_encrypt CDECL_NORM(aes_128_ecb_encrypt)
void	aes_128_ecb_encrypt(uint8_t *data, uint64_t size, uint8_t *key, uint64_t kye_size);

/**
 * Keygen
 */

void	gen_aes_key(uint8_t *dest, size_t size);

#endif /* AES_H */