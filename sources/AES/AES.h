#include <stdint.h>
#include <stddef.h>

/* Define constants and sbox */
#define Nb 4
#define Nk(keysize) ((int)(keysize / 32))
#define Nr(keysize) ((int)(Nk(keysize) + 6))



/* State and key types */
typedef uint8_t** State;
typedef uint8_t* Key;

/* My additional methods */
void encrypt(char* plain, char* key);
void decrypt(char* cipher, char* key);
State* toState(uint8_t* input);
uint8_t** fromState(State* state);
void freeState(State* state);
void stringToBytes(char* str, uint8_t* bytes);

/* AES main methods */
uint8_t** Cipher(uint8_t* input, uint8_t* keySchedule, size_t keySize);
uint8_t** InvCipher(uint8_t* input, uint8_t* w, size_t keySize);

/* AES sub-methods */
void _SubBytes(State* state, const uint8_t* box);
void SubBytes(State* state);
void InvSubBytes(State* state);
void _ShiftRows(State* state, int multiplier);
void ShiftRows(State* state);
void InvShiftRows(State* state);
void MixColumns(State* state);
void InvMixColumns(State* state);
void AddRoundKey(State* state, uint8_t* roundKey);
void KeyExpansion(uint8_t* key, uint8_t* keySchedule, size_t keySize);

/* AES sub-sub-methods and round constant array */
uint8_t* SubWord(uint8_t* a);
uint8_t* RotWord(uint8_t* a);
uint8_t* Rcon(int a);

/* AES helper methods */
uint8_t* xorWords(uint8_t* a, uint8_t* b);
uint8_t* copyWord(uint8_t* start);
uint8_t* getWord(uint8_t* w, int i);
uint8_t galoisMultiply(uint8_t a, uint8_t b);