#include "aes.h"
#include <stdint.h>

void MixColumns(uint8_t ***state){
	int c, r;
	for(c = 0; c < 4; c++){
		uint8_t temp[4];
		temp[0] = galoisMultiply(state[0][0][c], 2) ^ galoisMultiply(state[0][1][c], 3) ^ state[0][2][c] ^ state[0][3][c];
		temp[1] = state[0][0][c] ^ galoisMultiply(state[0][1][c], 2) ^ galoisMultiply(state[0][2][c], 3) ^ state[0][3][c];
		temp[2] = state[0][0][c] ^ state[0][1][c] ^ galoisMultiply(state[0][2][c], 2) ^ galoisMultiply(state[0][3][c], 3);
		temp[3] = galoisMultiply(state[0][0][c], 3) ^ state[0][1][c] ^ state[0][2][c] ^ galoisMultiply(state[0][3][c], 2);
		for(r = 0; r < 4; r++){
			state[0][r][c] = temp[r];
		}
	}
}

void InvMixColumns(uint8_t ***state){
	int c, r;
	for(c = 0; c < 4; c++){
		uint8_t temp[4];
		temp[0] = galoisMultiply(state[0][0][c], 14) ^ galoisMultiply(state[0][1][c], 11) ^ galoisMultiply(state[0][2][c], 13) ^ galoisMultiply(state[0][3][c], 9);
		temp[1] = galoisMultiply(state[0][0][c], 9)  ^ galoisMultiply(state[0][1][c], 14) ^ galoisMultiply(state[0][2][c], 11) ^ galoisMultiply(state[0][3][c], 13);
		temp[2] = galoisMultiply(state[0][0][c], 13) ^ galoisMultiply(state[0][1][c], 9)  ^ galoisMultiply(state[0][2][c], 14) ^ galoisMultiply(state[0][3][c], 11);
		temp[3] = galoisMultiply(state[0][0][c], 11) ^ galoisMultiply(state[0][1][c], 13) ^ galoisMultiply(state[0][2][c], 9)  ^ galoisMultiply(state[0][3][c], 14);
		for(r = 0; r < 4; r++){
			state[0][r][c] = temp[r];
		}
	}
}


uint8_t* getWord(uint8_t* w, int i)
{
	return &w[4*i];
}

void AddRoundKey(uint8_t ***state, uint8_t *keyCypher)
{
	int c, r;
	for(c = 0; c < 4; c++){
		for(r = 0; r < 4; r++){
			state[0][r][c] ^= *keyCypher;
			keyCypher++;
		}
	}
}

void SubBytes(uint8_t ***state){
	return(_SubBytes(state, sbox));
}

void InvSubBytes(uint8_t ***state){
	return(_SubBytes(state, isbox));
}

void _SubBytes(uint8_t ***state, const uint8_t* box){
	int i, j;
	uint8_t new;
	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			new = box[state[0][i][j]];
			state[0][i][j] = new;
		}
	}
}

void _ShiftRows(uint8_t ***state, int multiplier)
{
	int i, j;
	for(i = 0; i < 4; i++){
		uint8_t temp[4];
		for(j = 0; j < 4; j++){
			temp[((j + 4) + (multiplier * i)) % 4] = state[0][i][j];
		}
		memcpy(state[0][i], temp, 4);
	}

}

void ShiftRows(uint8_t ***state)
{
	return(_ShiftRows(state, -1));
}

void InvShiftRows(uint8_t ***state)
{
	return(_ShiftRows(state, 1));
}

void freeState(uint8_t **state){
	int i;
	for(i = 0; i < 4; i++)
		free(state[i]);
	free(state);
}

int8_t galoisMultiply(uint8_t a, uint8_t b)
{
	uint8_t p = 0;
	int i;
	int carry;
	for(i = 0; i < 8; i++){
		if((b & 1) == 1){
			p ^= a;
		}
		b >>= 1;
		carry = a & 0x80;
		a <<= 1;
		if(carry == 0x80){
			a ^= 0x1b;
		}
	}
	return p;
}


void stringToBytes(char* str, uint8_t* bytes)
{
	char pair[3];
	for(size_t i = 0; i < strlen(str) - 1; i += 2){
		pair[0] = str[i];
		pair[1] = str[i + 1];
		pair[2] = '\0';
		bytes[i/2] = strtol(pair, NULL, 16);
	}
}


uint8_t ***toState(uint8_t* input)
{
	int i, j;
	uint8_t *** stateptr = malloc(sizeof(uint8_t **));
	*stateptr = malloc(4 * sizeof(uint8_t*));
	uint8_t ** state = *stateptr;
	for(i = 0; i < 4; i++){
		state[i] = malloc(4 * sizeof(uint8_t));
	}
	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			state[j][i] = *input;
			input++;
		}
	}
	return stateptr;
}


uint8_t** fromState(uint8_t ***state)
{
	int i, j;
	uint8_t** outputptr = calloc(1, sizeof(uint8_t*));
	*outputptr = calloc(1, sizeof(uint8_t) * 17);
	uint8_t* output = *outputptr;
	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			*output = (*state)[j][i];
			output++;
		}
	}

	return outputptr;
}


static uint8_t* Rcon(int a)
{
	uint8_t rcon = 0x8d;
	int i;
	for(i = 0; i < a; i++){
		rcon = ((rcon << 1) ^ (0x11b & - (rcon >> 7)));
	}
	uint8_t* word = calloc(4, sizeof(uint8_t));
	word[0] = rcon;
	return word;
}

static uint8_t* xorWords(uint8_t* a, uint8_t* b)
{
	int i;
	uint8_t* init = a;
	for(i = 0; i < 4; i++, a++, b++){
		*a ^= *b;
	}
	return init;
}

static uint8_t* copyWord(uint8_t* start)
{
	int i;
	uint8_t* word = calloc(1, sizeof(uint8_t) * 5);
	for(i = 0; i < 4; i++, start++){
		word[i] = *start;
	}
	return word;
}


static uint8_t* SubWord(uint8_t* a)
{
	int i;
	uint8_t* init = a;
	for(i = 0; i < 4; i++){
		*a = sbox[*a];
		a++;
	}
	return init;
}

static uint8_t* RotWord(uint8_t* a)
{
	uint8_t rot[] = {a[1], a[2], a[3], a[0]};
	memcpy(a, rot, 4);
	return a;
}

void get_key_schedule(uint8_t* key, uint8_t* key_schedule){
	int i, j;
	uint8_t *wi, *wk, *temp, *rconval;
	for(i = 0; i < 8; i++){
		for(j = 0; j < 4; j++){
			key_schedule[4*i+j] = key[4*i+j];
		}
	}
	i = 8;
 	 while(i < 60){
		temp = copyWord(getWord(key_schedule, i-1));
		if(i % 8 == 0){
			rconval = Rcon(i/8);
			xorWords(SubWord(RotWord(temp)), rconval);
			free(rconval);
		} else if(i % 8 == 4){
			memcpy(temp, SubWord(temp), 4);
		}
		wi = getWord(key_schedule, i);
		wk = getWord(key_schedule, i - 8);
		memcpy(wi, xorWords(temp, wk), 4);
		free(temp);
		i++;
	}
}


void BytesToString(uint8_t* bytes, char* str){
	int i;
	for(i = 0; i < 16; i++){
		sprintf(str + (i * 2), "%02x", bytes[i]);
	}
}
