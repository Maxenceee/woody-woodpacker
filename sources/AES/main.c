// #include "aes.h"
// #include <stdio.h>


// int main(int argc, char **argv)
// {
// 	if (argc != 3)
// 		return (0);

// 	// printf("before  : ");
// 	// printf("%s\n", argv[1]);
// 	// printf("before : %s | %s\n", argv[1], argv[2]);
// 	uint8_t **encoded = AES_encrypt(argv[1], argv[2]);
// 	if (encoded == NULL)
// 	{
// 		printf("error\n");
// 		return(0);
// 	}
// 	// printf("encrypted : %s | %s\n", argv[1], argv[2]);
// 	// decrypt(argv[1], argv[2]);
// 	// printf("decrypted : %s | %s\n", argv[1], argv[2]);
// 	printf("encoded : ");
//     for(int i = 0; i < 16; i++){
//         printf("%02x", (*encoded)[i]);
//     }
// 	printf("\n");
// 	// return(0);
// 	char *str = calloc(1, 256);
// 	BytesToString(*encoded, str);
// 	uint8_t **decoded = AES_decrypt(str, argv[2]);
// 	// 	if (encoded == NULL)
// 	// {
// 	// 	printf("error\n");
// 	// 	return(0);
// 	// }
// 	// printf("decoded : ");
// 	// for (int i = 0; i < 16; i++)
// 	// {
// 	// 	printf("%02x ", encoded[i]);
// 	// }
// 	// printf("\n");
// 	printf("decoded : ");
//     for(int i = 0; i < 16; i++){
//         printf("%02x", (*decoded)[i]);
//     }
// 	printf("\n");
// 	free(encoded[0]);
// 	free(encoded);
// 	free(decoded[0]);
// 	free(decoded);
// 	free(str);
// 	return (0);
// }