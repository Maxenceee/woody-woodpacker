#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stddef.h>
#include "AES.h"
#include "AES_const.c"

// int main(){
    // /* Examples of encryption */
    // printf("ENCRYPTION:\n");
    // encrypt("3243f6a8885a308d313198a2e0370734", "2b7e151628aed2a6abf7158809cf4f3c"); /* Appendix B example */
    // encrypt("00112233445566778899aabbccddeeff", "000102030405060708090a0b0c0d0e0f"); /* Appendix C 128-bit example */
    // encrypt("00112233445566778899aabbccddeeff", "000102030405060708090a0b0c0d0e0f1011121314151617"); /* Appendix C 192-bit example */
    // encrypt("00112233445566778899aabbccddeeff", "000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f"); /* Appendix C 256-bit example */
    // /* Inverse of the above */
    // printf("DECRYPTION:\n");
    // decrypt("3925841d02dc09fbdc118597196a0b32", "2b7e151628aed2a6abf7158809cf4f3c");
    // decrypt("69c4e0d86a7b0430d8cdb78070b4c55a", "000102030405060708090a0b0c0d0e0f");
    // decrypt("dda97ca4864cdfe06eaf70a0ec0d7191", "000102030405060708090a0b0c0d0e0f1011121314151617");
    // decrypt("8ea2b7ca516745bfeafc49904b496089", "000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f");
    // return 0;
// }

void AES_main(char* text, char* keyStr, int encrypting){
    /* 
       Takes a 128-bit hexadecimal string plaintext and
       128-, 192- or 256- bit hexadecimal string key and
       applies AES encryption or decryption. 
    */
    uint8_t *keySchedule, **output;
    int i;
    /* Convert input string to state */
    uint8_t* input = malloc(sizeof(uint8_t) * 16);
    stringToBytes(text, input);
    /* Convert key string to bytes */
    size_t keyBytes = (sizeof(uint8_t)*strlen(keyStr))/2;
    Key key = malloc(keyBytes);
    stringToBytes(keyStr, key);
    /* Convert number of bytes to bits */
    size_t keySize = keyBytes * 8;
    /* Create array for key schedule */
    keySchedule = calloc(4 * Nb * (Nr(keySize) + 1), sizeof(uint8_t));
    /* Expand key */
    KeyExpansion(key, keySchedule, keySize);
    /* Run cipher */
    if(encrypting){
        output = Cipher(input, keySchedule, keySize);
    } else{
        output = InvCipher(input, keySchedule, keySize);
    }
    /* Display result */
    for(i = 0; i < 16; i++){
        printf("%02x", (*output)[i]);
    }
    printf("\n");
    /* Free memory */
    free(input);
    free(key);
    free(keySchedule);
    free(*output);
    free(output);
}

void encrypt(char* plaintext, char* keyStr){
    AES_main(plaintext, keyStr, 1);
}

void decrypt(char* ciphertext, char* keyStr){
    AES_main(ciphertext, keyStr, 0);
}

/* 
    AES main methods
*/
void KeyExpansion(uint8_t* key, uint8_t* w, size_t keySize){
    /*
        Takes a 128-, 192- or 256-bit key and applies the
        key expansion algorithm to produce a key schedule.
    */
    int i, j;
    uint8_t *wi, *wk, *temp, *rconval;
    /* Copy the key into the first Nk words of the schedule */
    for(i = 0; i < Nk(keySize); i++){
        for(j = 0; j < Nb; j++){
            w[4*i+j] = key[4*i+j];
        }
    }
    i = Nk(keySize);
    /* Generate Nb * (Nr + 1) additional words for the schedule */
    while(i < Nb * (Nr(keySize) + 1)){
        /* Copy the previous word */
        temp = copyWord(getWord(w, i-1));
        if(i % Nk(keySize) == 0){
            /* If i is divisble by Nk, rotate and substitute the word
               and then xor with Rcon[i/Nk] */
            rconval = Rcon(i/Nk(keySize));
            xorWords(SubWord(RotWord(temp)), rconval);
            free(rconval);
        } else if(Nk(keySize) > 6 && i % Nk(keySize) == 4){
            /* If Nk > 6 and i mod Nk is 4 then just substitute */
            memcpy(temp, SubWord(temp), 4);
        }
        /* Get pointers for the current word and the (i-Nk)th word */
        wi = getWord(w, i);
        wk = getWord(w, i - Nk(keySize));
        /* wi = temp xor wk */
        memcpy(wi, xorWords(temp, wk), 4);
        free(temp);
        i++;
    }
}

uint8_t** Cipher(uint8_t* input, uint8_t* w, size_t keySize){
    /*
        AES Cipher method - Takes a 128 bit array of bytes and
        the key schedule and applies the cipher algorithm,
        returning a pointer to an array of output.
    */
    int i;
    uint8_t** output;
    State* state = toState(input);

    /* Cipher method */
    AddRoundKey(state, getWord(w, 0));
    for(i = 1; i < Nr(keySize); i++){
        SubBytes(state);
        ShiftRows(state);
        MixColumns(state);
        AddRoundKey(state, getWord(w, i*Nb));
    }
    SubBytes(state);
    ShiftRows(state);
    AddRoundKey(state, getWord(w, Nr(keySize)*Nb));
    
    output = fromState(state);
    freeState(state);
    return output;
}

uint8_t** InvCipher(uint8_t* input, uint8_t* w, size_t keySize){
    /*
        AES InvCipher method - Takes 128 bits of cipher text and the
        key schedule and applies the inverse cipher, returning a
        pointer to an array of plaintext bytes.
    */
    int i;
    uint8_t** output;
    State* state = toState(input);

    /* Inverse cipher method */
    AddRoundKey(state, getWord(w, Nr(keySize) * Nb));
    for(i = Nr(keySize) - 1; i >= 1; i--){
        InvShiftRows(state);
        InvSubBytes(state);
        AddRoundKey(state, getWord(w, i*Nb));
        InvMixColumns(state);
    }
    InvShiftRows(state);
    InvSubBytes(state);
    AddRoundKey(state, getWord(w, 0));

    output = fromState(state);
    freeState(state);
    return output;
}

/*
    State to/from and helper methods
*/
State* toState(uint8_t* input){
    /*
        Takes an array of bytes and returns
        a pointer to a State.
    */
    int i, j;
    /* Malloc state pointer and state.
       The state pointer is returned because
       it is more useful than the state itself */
    State* stateptr = malloc(sizeof(State));
    *stateptr = malloc(4 * sizeof(uint8_t*));
    State state = *stateptr;
    for(i = 0; i < 4; i++){
        state[i] = malloc(Nb * sizeof(uint8_t));
    }
    /* Fill state */
    for(i = 0; i < 4; i++){
        for(j = 0; j < Nb; j++){
            /* Set value in state array to current byte
               j and i are swapped because the input is
               transposed */
            state[j][i] = *input;
            /* Increment pointer */
            input++;
        }
    }
    return stateptr;
}

uint8_t** fromState(State* state){
    /*
        Takes a State and returns a pointer
        to an array of bytes.
    */
    int i, j;
    /* Malloc outputptr and output */
    uint8_t** outputptr = malloc(sizeof(uint8_t*));
    *outputptr = malloc(sizeof(uint8_t) * 16);
    uint8_t* output = *outputptr;
    /* Fill output */
    for(i = 0; i < 4; i++){
        for(j = 0; j < Nb; j++){
            /* Set the output to it's array item,
               transposing the state */
            *output = (*state)[j][i];
            /* Increment the pointer */
            output++;
        }
    }
    return outputptr;
}

void freeState(State* state){
    /*
        Free the memory used by each row, the
        state itself and the pointer to the state.
    */
    int i;
    for(i = 0; i < 4; i++){
        free((*state)[i]);
    }
    free(*state);
    free(state);
}

void stringToBytes(char* str, uint8_t* bytes){
    /*
        Converts a hexadecimal string of bytes into an
        array of uint8_t.
    */
    int i;
    for(i = 0; i < strlen(str) - 1; i += 2){
        /* Allocate space for pair of nibbles */
        char* pair = malloc(2 * sizeof(char));
        /* Copy current and next character to pair */
        memcpy(pair, &str[i], 2);
        /* Use strtol to convert string to long, which is
           implicitly converted to a uint8_t. This is stored
           in index i/2 as there are half as many bytes as
           hex characters */
        bytes[i/2] = strtol(pair, NULL, 16);
        free(pair);
    }
}

/*
    AES sub-methods
*/
void _SubBytes(State* state, const uint8_t* box){
    /*
        Generalised SubBytes method which takes the
        S-box to use as an argument.
    */
    int i, j;
    for(i = 0; i < 4; i++){
        for(j = 0; j < Nb; j++){
            /* Get the new value from the S-box */
            uint8_t new = box[(*state)[i][j]];
            (*state)[i][j] = new;
        }
    }
}

void SubBytes(State* state){
    _SubBytes(state, sbox);
}

void InvSubBytes(State* state){
    _SubBytes(state, isbox);
}

void _ShiftRows(State* state, int multiplier){
    /*
        Generalised ShiftRows method which takes a multiplier
        which affects the shift direction.
    */
    int i, j;
    for(i = 0; i < 4; i++){
        /* The row number is the number of shifts to do */
        uint8_t temp[4];
        for(j = 0; j < Nb; j++){
            /* The multiplier determines whether to do a left or right shift */
            temp[((j + Nb) + (multiplier * i)) % Nb] = (*state)[i][j];
        }
        /* Copy temp array to state array */
        memcpy((*state)[i], temp, 4);
    }
}

void ShiftRows(State* state){
    _ShiftRows(state, -1);
}

void InvShiftRows(State* state){
    _ShiftRows(state, 1);
}

uint8_t galoisMultiply(uint8_t a, uint8_t b){
    /*
        Multiplies two bytes in the 2^8 Galois field.
        Implementation based on description from https://en.wikipedia.org/wiki/Finite_field_arithmetic#Rijndael's_(AES)_finite_field
    */
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

void MixColumns(State* state){
    /*
        Applies the MixColumns method to the state.
        See Section 5.1.3 of the standard for explanation.
    */
    int c, r;
    for(c = 0; c < Nb; c++){
        uint8_t temp[4];
        temp[0] = galoisMultiply((*state)[0][c], 2) ^ galoisMultiply((*state)[1][c], 3) ^ (*state)[2][c] ^ (*state)[3][c];
        temp[1] = (*state)[0][c] ^ galoisMultiply((*state)[1][c], 2) ^ galoisMultiply((*state)[2][c], 3) ^ (*state)[3][c];
        temp[2] = (*state)[0][c] ^ (*state)[1][c] ^ galoisMultiply((*state)[2][c], 2) ^ galoisMultiply((*state)[3][c], 3);
        temp[3] = galoisMultiply((*state)[0][c], 3) ^ (*state)[1][c] ^ (*state)[2][c] ^ galoisMultiply((*state)[3][c], 2);
        /* Copy temp array to state */
        for(r = 0; r < 4; r++){
            (*state)[r][c] = temp[r];
        }
    }
}

void InvMixColumns(State* state){
    /*
        Applies InvMixColumns to the state.
        See Section 5.3.3 of the standard for explanation.
    */
    int c, r;
    for(c = 0; c < Nb; c++){
        uint8_t temp[4];
        temp[0] = galoisMultiply((*state)[0][c], 14) ^ galoisMultiply((*state)[1][c], 11) ^ galoisMultiply((*state)[2][c], 13) ^ galoisMultiply((*state)[3][c], 9);
        temp[1] = galoisMultiply((*state)[0][c], 9)  ^ galoisMultiply((*state)[1][c], 14) ^ galoisMultiply((*state)[2][c], 11) ^ galoisMultiply((*state)[3][c], 13);
        temp[2] = galoisMultiply((*state)[0][c], 13) ^ galoisMultiply((*state)[1][c], 9)  ^ galoisMultiply((*state)[2][c], 14) ^ galoisMultiply((*state)[3][c], 11);
        temp[3] = galoisMultiply((*state)[0][c], 11) ^ galoisMultiply((*state)[1][c], 13) ^ galoisMultiply((*state)[2][c], 9)  ^ galoisMultiply((*state)[3][c], 14);
        /* Copy temp array to state */
        for(r = 0; r < 4; r++){
            (*state)[r][c] = temp[r];
        }
    }
}

void AddRoundKey(State* state, uint8_t* roundKey){
    /*
        Takes a pointer to the start of a round key
        and XORs it with the columns of the state.
    */
    int c, r;
    for(c = 0; c < Nb; c++){
        for(r = 0; r < 4; r++){
            /* XOR each column with the round key */
            (*state)[r][c] ^= *roundKey;
            roundKey++;
        }
    }
}

/*
    AES sub-sub-methods
*/
uint8_t* SubWord(uint8_t* a){
    /*
        Substitute bytes in a word using the sbox.
    */
    int i;
    uint8_t* init = a;
    for(i = 0; i < 4; i++){
        *a = sbox[*a];
        a++;
    }
    return init;
}

uint8_t* RotWord(uint8_t* a){
    /*
        Rotate word then copy to pointer.
    */
    uint8_t rot[] = {a[1], a[2], a[3], a[0]};
    memcpy(a, rot, 4);
    return a;
}

uint8_t* Rcon(int a){
    /* Calculates the round constant and returns it in an array.
       This implementation is adapted from
       https://github.com/secworks/aes/blob/6fb0aef25df082d68da9f75e2a682441b5f9ff8e/src/model/python/rcon.py#L180
    */
    uint8_t rcon = 0x8d;
    int i;
    for(i = 0; i < a; i++){
        rcon = ((rcon << 1) ^ (0x11b & - (rcon >> 7)));
    }
    /* The round constant array is always of the form [rcon, 0, 0, 0] */
    uint8_t* word = calloc(4, sizeof(uint8_t));
    word[0] = rcon;
    return word;
}

/*
    Word helper methods
*/
uint8_t* xorWords(uint8_t* a, uint8_t* b){
    /* Takes the two pointers to the start of 4 byte words and
       XORs the words, overwriting the first. Returns a pointer to
       the first byte of the first word. */
    int i;
    uint8_t* init = a;
    for(i = 0; i < 4; i++, a++, b++){
        *a ^= *b;
    }
    return init;
}

uint8_t* copyWord(uint8_t* start){
    /*
        Returns a pointer to a copy of a word.
    */
    int i;
    uint8_t* word = malloc(sizeof(uint8_t) * 4);
    for(i = 0; i < 4; i++, start++){
        word[i] = *start;
    }
    return word;
}

uint8_t* getWord(uint8_t* w, int i){
    /*
        Takes a word number (w[i] in spec) and
        returns a pointer to the first of it's 4 bytes.
    */
    return &w[4*i];
}