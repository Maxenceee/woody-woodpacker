// #include "aes.h"
// #include <stdio.h>


// void AES_256_Key_Expansion (const unsigned char *userkey, unsigned char *key);
// void AES_CTR_encrypt (const unsigned char *in, unsigned char *out, const unsigned char ivec[8], const unsigned char nonce[4], unsigned long length, const unsigned char *key, int nr);
// int main(int argc, char **argv)
// {

// 	unsigned char *key;
// 	unsigned char *cypher;
// 	key = calloc(1, sizeof(unsigned char) * 256);
// 	cypher = calloc(1, sizeof(unsigned char) * 256);
// 	printf("'%s'\n", key);
// 	AES_256_Key_Expansion((const unsigned char *)argv[1], key);
// 	printf("'%s'\n", key);
// 	unsigned char nonce[4] = {0x00, 0xFA, 0xAC, 0x24};
// 	unsigned char IV[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00};
// 	AES_CTR_encrypt((unsigned char *)argv[2], cypher, IV , nonce, 64, key, 64);

// 	printf("'%s'\n", cypher);
// 	AES_CTR_encrypt(cypher, cypher, IV , nonce, 64, key, 64);
// 	printf("'%s'\n", cypher);
// 	free(key);
// 	free(cypher);
// }


// mandatory part and how it work