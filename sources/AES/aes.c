
#include "aes.h"

void freeState(uint8_t **state){
	int i;
	for(i = 0; i < 4; i++)
		free(state[i]);
	free(state);
}

 //take the plaintext and the key as arguments, fixed size of each, will die otherwise
char *AES_encrypt(char *plaintext, char *key)
{
	char        *ciphertext;
	int         len;

	len = strlen(plaintext);
	ciphertext = calloc(1, len + 1);
	if (!ciphertext || !key || strlen(key) != 32|| !plaintext || len != 16)
		return (NULL);
	
	int keyCypher[60];			//generate key schedule
	int i;
	uint32_t temp;
	for(i = 0; i < 8; i++)
       keyCypher[i] = LOAD32LE(key + (i * 4));
	for(i = 8; i < 60; i++)
    {
       temp = keyCypher[i - 1];
       if((i % 8) == 0)
       {
          keyCypher[i] = sbox[(temp >> 8) & 0xFF];
          keyCypher[i] |= (sbox[(temp >> 16) & 0xFF] << 8);
          keyCypher[i] |= (sbox[(temp >> 24) & 0xFF] << 16);
          keyCypher[i] |= (sbox[temp & 0xFF] << 24);
          keyCypher[i] ^= rcon[i / 8];
       }
       else if(i % 8 == 4)
       {
          keyCypher[i] = sbox[temp & 0xFF];
          keyCypher[i] |= (sbox[(temp >> 8) & 0xFF] << 8);
          keyCypher[i] |= (sbox[(temp >> 16) & 0xFF] << 16);
          keyCypher[i] |= (sbox[(temp >> 24) & 0xFF] << 24);
       }
       else
          keyCypher[i] = temp;
  
       keyCypher[i] ^= keyCypher[i - 8];
    }
	uint8_t *bytes = calloc(1, sizeof(uint8_t) * 16);

	if (!bytes)
		return (NULL);
	for(int i = 0; i < 15; i += 2){
       	char* pair = calloc(1, 2 * sizeof(char));
	   	if (!pair)
	   		return (free(ciphertext), free(bytes), NULL);
      	memcpy(pair, &plaintext[i], 2);
      	bytes[i/2] = strtol(pair, NULL, 16);
      	free(pair);
    }

	uint8_t **state;
	state = calloc(1, 4 * sizeof(uint8_t *));
	for (int i = 0; i < 4; i++)
		state[i] = calloc(1, 4 * sizeof(uint8_t));
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			state[j][i] = *bytes;
			bytes++;
		}
	}
	free(bytes - 16);
	state = AddRoundKey(state, keyCypher);



	for (int i = 0; i < 14; i++)
	{
		state = SubBytes(state);
	// 	// state = ShiftRows(state);
	// 	// state = MixColumns(state);
	// 	// state = AddRoundKey(state, keyCypher + (i * 4), plaintext);
	}
		for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			printf("%x\n",state[j][i]);

	}
	freeState(state);
	return (ciphertext);
}


uint8_t **AddRoundKey(uint8_t **state, int keyCypher[60])
{
    int c, r;
    for(c = 0; c < 4; c++){
        for(r = 0; r < 4; r++){
            state[r][c] ^= *keyCypher;
            keyCypher++;
        }
    }
	return(state);
}

uint8_t **SubBytes(uint8_t** state){
    return(_SubBytes(state, sbox));
}

uint8_t **InvSubBytes(uint8_t** state){
   return(_SubBytes(state, isbox));
}

uint8_t **_SubBytes(uint8_t** state, const uint8_t* box){
    int i, j;
    for(i = 0; i < 4; i++){
        for(j = 0; j < 4; j++){
            /* Get the new value from the S-box */
            uint8_t new = box[state[i][j]];
            state[i][j] = new;
        }
    }
	return(state);
}