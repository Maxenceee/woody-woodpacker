
#include "aes.h"
#include <stdint.h>
#include <stdio.h>


 //take the plaintext and the key as arguments, fixed size of each, will die otherwise
uint8_t **AES_encrypt(char *plaintext, char *key)
{
	if (!plaintext || !key)
		return (NULL);
	uint8_t *key_schedule = calloc(1, 240 * sizeof(uint8_t));

	uint8_t *keyBytes = calloc(1, 32);
	uint8_t *input = calloc(1, 16);
	stringToBytes(plaintext, input);
	stringToBytes(key, keyBytes);
	get_key_schedule(keyBytes, key_schedule);
	uint8_t ***state = toState(input);
	

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
	free(keyBytes);
	free(input);
	return (ciphertext);
}

uint8_t **AES_decrypt(char *plaintext, char *key)
{
	if (!plaintext || !key)
		return (NULL);
	uint8_t *key_schedule = calloc(1, 240 * sizeof(uint8_t));

	uint8_t *keyBytes = calloc(1, 32);
	get_key_schedule(keyBytes, key_schedule);
	uint8_t *input = calloc(1, 16);
	stringToBytes(plaintext, input);
	stringToBytes(key, keyBytes);
	uint8_t ***state = toState(input);
	


	AddRoundKey(state, getWord(key_schedule, 56));
	for (int i = 13; i >= 1; i--)
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
	free(keyBytes);
	free(input);
	return (ciphertext);
}
