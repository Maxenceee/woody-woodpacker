/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aes.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 14:17:15 by mgama             #+#    #+#             */
/*   Updated: 2024/07/16 19:29:13 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AES_H
# define AES_H

#include "types.h"

#define AES_256_Key_Expansion CDECL_NORM(AES_256_Key_Expansion)
#define AES_CTR_encrypt CDECL_NORM(AES_CTR_encrypt)

void	AES_256_Key_Expansion(const unsigned char *userkey, unsigned char *key);
void	AES_CTR_encrypt(const unsigned char *in, unsigned char *out, const unsigned char ivec[8], const unsigned char nonce[4], unsigned long length, const unsigned char *key, int nr);

#endif /* AES_H */