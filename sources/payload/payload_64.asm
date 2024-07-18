global _payload_64
global _payload_64_size
global _AES_CTR_encrypt2
global _AES_256_Key_Expansion2
extern malloc


%ifdef __APPLE__
%define JUMP_ADDR [rel 0x0]
%else
%define JUMP_ADDR 0x0
%endif

[BITS 64]

segment .text align=16
malloc_ptr dq malloc

_payload_64:
	push rax
	push rdx
	push rsi
	push rdi


	mov	rsi, 256
	mov rdx, 0x3
	mov r10, 0x22
	mov r8, -1
	mov r9, 0
	xor rdi, rdi
	mov rax, 9
	syscall
	mov rdi, rax
	mov	rsi, key
	; mov	rsi, f_key
	mov rsi, rax
	call _AES_256_Key_Expansion2
	push rsi
	mov	rsi, [rel encrypted_data_size]
	mov rdx, 0x3
	mov r10, 0x22
	mov r8, -1
	mov r9, 0
	xor rdi, rdi
	mov rax, 9
	syscall
; # 	[parameter 1: %rdi]
; # 	[parameter 2: %rsi]
; # 	[parameter 3: %rdx]
; # 	[parameter 4: %rcx]
; # 	[parameter 5: %r8]
; # 	[parameter 6: %r9]
; # 	[parameter 7: 8 + %rsp]
	mov rdi, [rel encrypted_data_start]
	mov rsi, rax
	mov rdx, IV
	mov rcx, [rel nonce]
	mov r8, encrypted_data_size
	pop r9
	mov rax, 64
	push rax
	call _AES_CTR_encrypt2
	call _PRINT







	jmp .print_start_msg
.displayed_str:
	db "....WOODY....", 0x0a, 0
.print_start_msg:
	mov rax, 0x1
	mov rdi, 1
	lea rsi, [rel .displayed_str]
	mov rdx, 15
	syscall
	pop rdi
	pop rsi
	pop rdx
	pop rax
	ret
	; jmp JUMP_ADDR; tkt le compilo veut une vraie adresse

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

_AES_CTR_encrypt2:	; basic label
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
pinsrq 	xmm0,	[rdx],	1			;crash here right now
pinsrd 	xmm0,	[rcx],	1			;crash here right now
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


_PRINT:	; basic label
	push rbx
    push rbp
    push r12
    push r13
    push r14
    push r15
	mov rax, 1
	mov rdi, 1
	mov rdx, 6
	lea rsi, [rel hello_message]
	syscall
    pop r15
    pop r14
    pop r13
    pop r12
    pop rbp
    pop rbx
	ret

_AES_256_Key_Expansion2:	; basic label
; # 	[parameter 1: %rdi]
; # 	[parameter 2: %rsi]
movdqu 	xmm1,	[rdi]
movdqu 	xmm3,	[16+rdi]
movdqa 	[rsi],	xmm1
movdqa 	[16+rsi],	xmm3
aeskeygenassist 	xmm2,	xmm3,	01h
call 	MAKE_RK256_a
movdqa 	[32+rsi],	xmm1
aeskeygenassist 	xmm2,	xmm1,	00h
call 	MAKE_RK256_b
movdqa 	[48+rsi],	xmm3
aeskeygenassist 	xmm2,	xmm3,	02h
call 	MAKE_RK256_a
movdqa 	[64+rsi],	xmm1
aeskeygenassist 	xmm2,	xmm1,	00h
call 	MAKE_RK256_b
movdqa 	[80+rsi],	xmm3
aeskeygenassist 	xmm2,	xmm3,	04h
call 	MAKE_RK256_a
movdqa 	[96+rsi],	xmm1
aeskeygenassist 	xmm2,	xmm1,	00h
call 	MAKE_RK256_b
movdqa 	[112+rsi],	xmm3
aeskeygenassist 	xmm2,	xmm3,	08h
call 	MAKE_RK256_a
movdqa 	[128+rsi],	xmm1
aeskeygenassist 	xmm2,	xmm1,	00h
call 	MAKE_RK256_b
movdqa 	[144+rsi],	xmm3
aeskeygenassist 	xmm2,	xmm3,	010h
call 	MAKE_RK256_a
movdqa 	[160+rsi],	xmm1
aeskeygenassist 	xmm2,	xmm1,	00h
call 	MAKE_RK256_b
movdqa 	[176+rsi],	xmm3
aeskeygenassist 	xmm2,	xmm3,	020h
call 	MAKE_RK256_a
movdqa 	[192+rsi],	xmm1
aeskeygenassist 	xmm2,	xmm1,	00h
call 	MAKE_RK256_b
movdqa 	[208+rsi],	xmm3
aeskeygenassist 	xmm2,	xmm3,	040h
call 	MAKE_RK256_a
movdqa 	[224+rsi],	xmm1
ret
MAKE_RK256_a:	; basic label
pshufd 	xmm2,	xmm2,	0ffh
movdqa 	xmm4,	xmm1
pslldq 	xmm4,	4
pxor 	xmm1,	xmm4
pslldq 	xmm4,	4
pxor 	xmm1,	xmm4
pslldq 	xmm4,	4
pxor 	xmm1,	xmm4
pxor 	xmm1,	xmm2
ret
MAKE_RK256_b:	; basic label
pshufd 	xmm2,	xmm2,	0aah
movdqa 	xmm4,	xmm3
pslldq 	xmm4,	4
pxor 	xmm3,	xmm4
pslldq 	xmm4,	4
pxor 	xmm3,	xmm4
pslldq 	xmm4,	4
pxor 	xmm3,	xmm4
pxor 	xmm3,	xmm2
ret


info_start:
key:					dq	"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
encrypted_data_start:	dq  0xbbbbbbbbbbbbbbbb
encrypted_data_size:	dq	0xcccccccccccccccc
hello_message: 			db 'hello', 0xA  ; "hello\n"
IV:						dq 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
nonce:					dq 0x00, 0xFA, 0xAC, 0x24
f_key:					dq	"bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb"
_payload_64_size:		dq $-_payload_64