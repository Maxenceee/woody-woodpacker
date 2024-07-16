global _payload_64
global _payload_64_size

[BITS 64]

segment .text align=16

_payload_64:
	push rax
	push rdx
	push rsi
	push rdi
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
	jmp	0x0 ; tkt le compilo veut une vraie adresse

info_start:
key:					dq	"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
encrypted_data_start:	dq  0xbbbbbbbbbbbbbbbb
encrypted_data_size:	dq	0xcccccccccccccccc
start_encode:			dq  0xdddddddddddddddd
_payload_64_size:		dq $-_payload_64