/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aes.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 14:17:15 by mgama             #+#    #+#             */
/*   Updated: 2024/06/28 15:03:33 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AES_H
# define AES_H

void	_AES_256_Key_Expansion (const unsigned char *userkey, unsigned char *key);
void	_AES_CTR_encrypt (const unsigned char *in, unsigned char *out, const unsigned char ivec[8], const unsigned char nonce[4], unsigned long length, const unsigned char *key, int nr);

#define AES_256_Key_Expansion _AES_256_Key_Expansion
#define AES_CTR_encrypt _AES_CTR_encrypt

#endif /* AES_H */