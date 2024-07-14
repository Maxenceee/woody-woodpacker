global _payload_64

[BITS 64]

segment .text align=16

_payload_64:
  push rax
  push rdi
  push rsi
  push rsp
  push rdx
  push rcx
  push rbx
  call get_my_loc
    sub edx, next_i - msg
    mov ecx, edx
    mov edx, msg_len
    mov ebx, 1
    mov eax, 4
    syscall

get_my_loc:
    call next_i

next_i:
    pop rdx
    ret

msg	db "....WOODY....", 0x0a, 0
msg_len	equ	$ - msg

clean:
    ; Reset the stack
    add rsp, 160
  pop rbx
  pop rcx
  pop rdx
  pop rsp
  pop rsi
  pop rdi
  pop rax
    ; jmp	0xFFFFFFFF
  ret

info_start:
key:					dq	"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
encrypted_data_start:	dq  0xbbbbbbbbbbbbbbbb
encrypted_data_len:		dq	0xcccccccccccccccc
start_encode:			dq  0xdddddddddddddddd
