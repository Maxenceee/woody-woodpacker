
#include "aes.h"
#include <stdint.h>
#include <stdio.h>

void	printbytes(uint8_t *bytes, size_t size);

//take the plaintext and the key as arguments, fixed size of each, will die otherwise
uint8_t **AES_encrypt(uint8_t *plaintext, char *key)
{
	if (!plaintext || !key)
		return (NULL);


	// printf("key -> %s\n", key);
	uint8_t *key_schedule = calloc(240, sizeof(uint8_t));
	get_key_schedule(key, key_schedule);

	uint8_t ***state = toState(plaintext);
	AddRoundKey(state, getWord(key_schedule, 0));

	for (int i = 1; i < 14; i++)
	{

		SubBytes(state);
		ShiftRows(state);
		MixColumns(state);
		AddRoundKey(state, getWord(key_schedule, i * 4));
	}

	SubBytes(state);
	ShiftRows(state);
	AddRoundKey(state, getWord(key_schedule, 56));

    uint8_t** ciphertext;
	ciphertext = fromState(state);

	freeState(*state);
	free(state);
	free(key_schedule);

	return (ciphertext);
}

uint8_t **AES_decrypt(uint8_t *plaintext, char *key)
{
    if (!plaintext || !key)
		return (NULL);

	uint8_t *key_schedule = calloc(240, sizeof(uint8_t));
	get_key_schedule(key, key_schedule);

	// printf("key 2 -> %s\n", key);
	uint8_t ***state = toState(plaintext);
	AddRoundKey(state, getWord(key_schedule, 56));

	for (int i = 13; i > 0; i--)
	{

		InvShiftRows(state);
		InvSubBytes(state);
		AddRoundKey(state, getWord(key_schedule, i * 4));
		InvMixColumns(state);
	}

	InvShiftRows(state);
	InvSubBytes(state);
	AddRoundKey(state, getWord(key_schedule, 0));

    uint8_t** ciphertext;
	ciphertext = fromState(state);

	freeState(*state);
	free(state);
	free(key_schedule);
	return (ciphertext);
}
