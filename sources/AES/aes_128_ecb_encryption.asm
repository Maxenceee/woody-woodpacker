%macro pushx 1-*
 %rep %0
   push %1
   %rotate 1
 %endrep
%endmacro

%macro popx 1-*
  %rep %0
    %rotate -1
    pop %1
  %endrep
%endmacro

%macro aes_128_keygenassist 1-2
    aeskeygenassist xmm2, xmm1, %1
    call _key_expansion_128
    movdqu %2, xmm1
%endmacro

[BITS 64]

global _aes_128_ecb_encrypt

_key_expansion_128:
    pshufd xmm2, xmm2, 0xff
    vpslldq xmm3, xmm1, 0x4
    pxor xmm1, xmm3
    vpslldq xmm3, xmm1, 0x4
    pxor xmm1, xmm3
    vpslldq xmm3, xmm1, 0x4
    pxor xmm1, xmm3
    pxor xmm1, xmm2
    ret

; void aes_128_ecb_encrypt(char *data, size_t data_size, char *key, size_t key_size)
;                           rdi             rsi         rdx             r10
_aes_128_ecb_encrypt:
	pushfq
	pushx rax, rdi, rsi, rsp, rdx, rcx

    ; TODO
	; cmp r10, 128
    ; cmp data_size, ?

    ; 128 bit key
    movdqu xmm1, [rdx]

    ; Move the key in xmm0
    movdqu xmm0, xmm1

    ; Generating round keys
    ; 10 times
    aes_128_keygenassist 0x1, xmm4
    aes_128_keygenassist 0x2, xmm5
    aes_128_keygenassist 0x4, xmm6
    aes_128_keygenassist 0x8, xmm7
    aes_128_keygenassist 0x10, xmm8
    aes_128_keygenassist 0x20, xmm9
    aes_128_keygenassist 0x40, xmm10
    aes_128_keygenassist 0x80, xmm11
    aes_128_keygenassist 0x1b, xmm12
    aes_128_keygenassist 0x36, xmm13

    xor r8, r8

; We can't fully encrypt the .text data when it's not a 16bytes multiple - TOFIX
    sub rsi, 16
_aes_loop:
    ; Load .text plaintext section block in xmm15
    movdqu xmm15, [rdi + r8]

    ; Whitening step - Round 0
    pxor xmm15, xmm0 ; First xor

    aesenc xmm15, xmm4 ; Round 1
    aesenc xmm15, xmm5 ; Round 2
    aesenc xmm15, xmm6 ; Round 3
    aesenc xmm15, xmm7 ; Round 4
    aesenc xmm15, xmm8 ; Round 5
    aesenc xmm15, xmm9 ; Round 6
    aesenc xmm15, xmm10 ; Round 7
    aesenc xmm15, xmm11 ; Round 8
    aesenc xmm15, xmm12 ; Round 9
    aesenclast xmm15, xmm13 ; Round 10

    ; Load the encrypted .text section block
    movdqu [rdi + r8], xmm15

    add r8, 16
    cmp rsi, r8
    jle clean
    jmp _aes_loop

clean:
    popx rax, rdi, rsi, rsp, rdx, rcx
    popfq
    ret

