#include "aes.h"
#include <stdio.h>


void main(int argc, char **argv)
{
	if (argc != 3)
		return;

	// printf("before : %s | %s\n", argv[1], argv[2]);
	char *encoded = AES_encrypt(argv[1], argv[2]);
	// printf("encrypted : %s | %s\n", argv[1], argv[2]);
	// decrypt(argv[1], argv[2]);
	// printf("decrypted : %s | %s\n", argv[1], argv[2]);
	printf("encoded : %s\n", encoded);
	free(encoded);
}