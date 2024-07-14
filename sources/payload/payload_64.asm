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

global _payload_64

[BITS 32]

segment .text align=16

_payload_64:
	pushx eax, edi, esi, esp, edx, ecx, ebx
	call get_my_loc
    sub edx, next_i - msg
    mov ecx, edx
    mov edx, msg_len
    mov ebx, 1
    mov eax, 4
    int 0x80

get_my_loc:
    call next_i

next_i:
    pop edx
    ret

msg	db "....WOODY....", 0x0a, 0
msg_len	equ	$ - msg

clean:
    ; Reset the stack
    add esp, 160
	popx eax, edi, esi, esp, edx, ecx, ebx
    ; jmp	0xFFFFFFFF
	ret

info_start:
key:					dq	"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
encrypted_data_start:	dq  0xbbbbbbbbbbbbbbbb
encrypted_data_len:		dq	0xcccccccccccccccc
start_encode:			dq  0xdddddddddddddddd
