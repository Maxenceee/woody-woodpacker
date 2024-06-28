section .text


align 256
ONE:	; basic label
;  .quad 0x00000000,0x00000001

align 256
FOUR:	; basic label
 ; .quad 0x00000004,0x00000004

align 256
EIGHT:	; basic label
 ; .quad 0x00000008,0x00000008

align 256
TWO_N_ONE:	; basic label
 ; .quad 0x00000002,0x00000001

align 256
TWO_N_TWO:	; basic label
 ; .quad 0x00000002,0x00000002

align 256
LOAD_HIGH_BROADCAST_AND_BSWAP:	; basic label
dq  0x0b0a090807060504, 0x0f0e0d0c0b0a0908

align 256	
BSWAP_EPI_64:	; basic label
db  7, 6, 5, 4, 3, 2, 1, 0, 15, 14, 13, 12, 11, 10, 9, 8



section .text
global _AES_CTR_encrypt
_AES_CTR_encrypt:	; basic label
; # 	[parameter 1: %rdi]
; # 	[parameter 2: %rsi]
; # 	[parameter 3: %rdx]
; # 	[parameter 4: %rcx]
; # 	[parameter 5: %r8]
; # 	[parameter 6: %r9]
; # 	[parameter 7: 8 + %rsp]
mov 	r10,	r8
mov 	r12d,	DWORD [8+rsp]
shr 	r8,	4
shl 	r10,	60
je 	NO_PARTS_4
add 	r8,	1
NO_PARTS_4:	; basic label
mov 	r10,	r8
shl 	r10,	62
shr 	r10,	62
pinsrq 	xmm0,	[rdx],	1
pinsrd 	xmm0,	[rcx],	1
psrldq 	xmm0,	4
movdqa 	xmm2,	xmm0
pshufb 	xmm2,	[rel LOAD_HIGH_BROADCAST_AND_BSWAP]
paddq 	xmm2,	[rel TWO_N_ONE]
movdqa 	xmm1,	xmm2
paddq 	xmm2,	[rel TWO_N_TWO]
pshufb 	xmm1,	[rel BSWAP_EPI_64]
pshufb 	xmm2,	[rel BSWAP_EPI_64]
shr 	r8,	2
je 	REMAINDER_4
sub 	rsi,	64
sub 	rdi,	64
LOOP_4:	; basic label
add 	rsi,	64
add 	rdi,	64
movdqa 	xmm11,	xmm0
movdqa 	xmm12,	xmm0
movdqa 	xmm13,	xmm0
movdqa 	xmm14,	xmm0
shufpd 	xmm11,	xmm1,	2
shufpd 	xmm12,	xmm1,	0
shufpd 	xmm13,	xmm2,	2
shufpd 	xmm14,	xmm2,	0
pshufb 	xmm1,	[rel BSWAP_EPI_64]
pshufb 	xmm2,	[rel BSWAP_EPI_64]
movdqa 	xmm8,	[r9]
movdqa 	xmm9,	[16+r9]
movdqa 	xmm10,	[32+r9]
movdqa 	xmm7,	[48+r9]
paddq 	xmm1,	[rel FOUR]
paddq 	xmm2,	[rel FOUR]
pxor 	xmm11,	xmm8
pxor 	xmm12,	xmm8
pxor 	xmm13,	xmm8
pxor 	xmm14,	xmm8
pshufb 	xmm1,	[rel BSWAP_EPI_64]
pshufb 	xmm2,	[rel BSWAP_EPI_64]
aesenc 	xmm11,	xmm9
aesenc 	xmm12,	xmm9
aesenc 	xmm13,	xmm9
aesenc 	xmm14,	xmm9
aesenc 	xmm11,	xmm10
aesenc 	xmm12,	xmm10
aesenc 	xmm13,	xmm10
aesenc 	xmm14,	xmm10
aesenc 	xmm11,	xmm7
aesenc 	xmm12,	xmm7
aesenc 	xmm13,	xmm7
aesenc 	xmm14,	xmm7
movdqa 	xmm8,	[64+r9]
movdqa 	xmm9,	[80+r9]
movdqa 	xmm10,	[96+r9]
movdqa 	xmm7,	[112+r9]
aesenc 	xmm11,	xmm8
aesenc 	xmm12,	xmm8
aesenc 	xmm13,	xmm8
aesenc 	xmm14,	xmm8
aesenc 	xmm11,	xmm9
aesenc 	xmm12,	xmm9
aesenc 	xmm13,	xmm9
aesenc 	xmm14,	xmm9
aesenc 	xmm11,	xmm10
aesenc 	xmm12,	xmm10
aesenc 	xmm13,	xmm10
aesenc 	xmm14,	xmm10
aesenc 	xmm11,	xmm7
aesenc 	xmm12,	xmm7
aesenc 	xmm13,	xmm7
aesenc 	xmm14,	xmm7
movdqa 	xmm8,	[128+r9]
movdqa 	xmm9,	[144+r9]
movdqa 	xmm10,	[160+r9]
cmp 	r12d,	12
aesenc 	xmm11,	xmm8
aesenc 	xmm12,	xmm8
aesenc 	xmm13,	xmm8
aesenc 	xmm14,	xmm8
aesenc 	xmm11,	xmm9
aesenc 	xmm12,	xmm9
aesenc 	xmm13,	xmm9
aesenc 	xmm14,	xmm9
jb 	LAST_4
movdqa 	xmm8,	[160+r9]
movdqa 	xmm9,	[176+r9]
movdqa 	xmm10,	[192+r9]
cmp 	r12d,	14
aesenc 	xmm11,	xmm8
aesenc 	xmm12,	xmm8
aesenc 	xmm13,	xmm8
aesenc 	xmm14,	xmm8
aesenc 	xmm11,	xmm9
aesenc 	xmm12,	xmm9
aesenc 	xmm13,	xmm9
aesenc 	xmm14,	xmm9
jb 	LAST_4
movdqa 	xmm8,	[192+r9]
movdqa 	xmm9,	[208+r9]
movdqa 	xmm10,	[224+r9]
aesenc 	xmm11,	xmm8
aesenc 	xmm12,	xmm8
aesenc 	xmm13,	xmm8
aesenc 	xmm14,	xmm8
aesenc 	xmm11,	xmm9
aesenc 	xmm12,	xmm9
aesenc 	xmm13,	xmm9
aesenc 	xmm14,	xmm9
LAST_4:	; basic label
aesenclast 	xmm11,	xmm10
aesenclast 	xmm12,	xmm10
aesenclast 	xmm13,	xmm10
aesenclast 	xmm14,	xmm10
pxor 	xmm11,	[rdi]
pxor 	xmm12,	[16+rdi]
pxor 	xmm13,	[32+rdi]
pxor 	xmm14,	[48+rdi]
movdqu 	[rsi],	xmm11
movdqu 	[16+rsi],	xmm12
movdqu 	[32+rsi],	xmm13
movdqu 	[48+rsi],	xmm14
dec 	r8
jne 	LOOP_4
add 	rsi,	64
add 	rdi,	64
REMAINDER_4:	; basic label
cmp 	r10,	0
je 	END_4
shufpd 	xmm0,	xmm1,	2
IN_LOOP_4:	; basic label
movdqa 	xmm11,	xmm0
pshufb 	xmm0,	[rel BSWAP_EPI_64]
pxor 	xmm11,	[r9]
paddq 	xmm0,	[rel ONE]
aesenc 	xmm11,	[16+r9]
aesenc 	xmm11,	[32+r9]
pshufb 	xmm0,	[rel BSWAP_EPI_64]
aesenc 	xmm11,	[48+r9]
aesenc 	xmm11,	[64+r9]
aesenc 	xmm11,	[80+r9]
aesenc 	xmm11,	[96+r9]
aesenc 	xmm11,	[112+r9]
aesenc 	xmm11,	[128+r9]
aesenc 	xmm11,	[144+r9]
movdqa 	xmm2,	[160+r9]
cmp 	r12d,	12
jb 	IN_LAST_4
aesenc 	xmm11,	[160+r9]
aesenc 	xmm11,	[176+r9]
movdqa 	xmm2,	[192+r9]
cmp 	r12d,	14
jb 	IN_LAST_4
aesenc 	xmm11,	[192+r9]
aesenc 	xmm11,	[208+r9]
movdqa 	xmm2,	[224+r9]
IN_LAST_4:	; basic label
aesenclast 	xmm11,	xmm2
pxor 	xmm11,	[rdi]
movdqu 	[rsi],	xmm11
add 	rdi,	16
add 	rsi,	16
dec 	r10
jne 	IN_LOOP_4
END_4:	; basic label
ret 
