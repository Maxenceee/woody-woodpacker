global _payload_64
global _payload_size_64
extern puts

[BITS 64]

segment .text

_payload_64:
	pushf
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
.encrypt:
	mov rax, [rel encrypted_data_start]
	mov rdi, [rel encrypted_data_len]
	mov rsi, [rel start_encode]
	add rdi, rax

	pop rdi
	pop rsi
	pop rdx
	pop rax
	popf
	jmp [rel .encrypt]

info_start:
key:					dq	"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
encrypted_data_start:	dq  0xbbbbbbbbbbbbbbbb
encrypted_data_len:		dq	0xcccccccccccccccc
start_encode:			dq  0xdddddddddddddddd
_payload_size_64:		dq $-_payload_64
