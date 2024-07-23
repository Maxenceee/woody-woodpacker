global _aes_128_ecb_decrypt
global _aes_128_ecb_decrypt_size

; %ifdef __APPLE__
; %define JUMP_ADDR [rel 0x0]
; %else
; %define JUMP_ADDR 0x0
; %endif

; %macro pushx 1-*
;  %rep %0
;    push %1
;    %rotate 1
;  %endrep
; %endmacro

; %macro popx 1-*
;   %rep %0
;     %rotate -1
;     pop %1
;   %endrep
; %endmacro

; %macro aes_128_keygenassist 1-2
;     aeskeygenassist xmm2, xmm1, %1
;     call _key_expansion_128
;     movdqu %2, xmm1
; %endmacro

; [BITS 64]

; _aes_128_ecb_decrypt:
; 	pushx rax, rdi, rsi, rsp, rdx, rcx, rbx

; 	; sys_write
;     call _get_my_loc
;     sub rdx, next_i - msg
; 	mov rax, 0x1
;     mov rsi, rdx
; 	mov rdi, 1
; 	mov rdx, msg_len
; 	syscall

;     ; We save pie offset
;     call _get_my_loc
;     sub rdx, next_i - _aes_128_ecb_decrypt
;     mov rbx, rdx
;     call _get_my_loc
;     sub rdx, next_i - info_offset
;     sub rbx, [rdx]

;     jmp _start_unpacking

; ; Uses xmm1, xmm2 and xmm3
; _key_expansion_128:
;     pshufd xmm2, xmm2, 0xff
;     vpslldq xmm3, xmm1, 0x4
;     pxor xmm1, xmm3
;     vpslldq xmm3, xmm1, 0x4
;     pxor xmm1, xmm3
;     vpslldq xmm3, xmm1, 0x4
;     pxor xmm1, xmm3
;     pxor xmm1, xmm2
;     ret

; _get_my_loc:
;     call next_i

; next_i:
;     pop rdx
;     ret

; msg	db "....WOODY....", 0x0a, 0
; msg_len	equ	$ - msg

; _start_unpacking:
;     call _get_my_loc
;     sub rdx, next_i - info_addr
; 	mov	rax, [rdx]
; 	; We add PIE offset
;     add rax, rbx
;     call _get_my_loc
; 	sub rdx, next_i - info_key
;     movdqu xmm1, [rdx]
;     call _get_my_loc
; 	sub rdx, next_i - info_size
; 	mov	rdx, [rdx]

;     ; Move the key in xmm0 to backup
;     movdqu xmm0, xmm1

;     ; We don't have enough xmm registers in x86 to store every round keys, so we push them to the stack

;     ; Generating round keys

;     ; 10 times
;     aes_128_keygenassist 0x1, xmm4
;     aesimc xmm4, xmm4
;     sub rsp, 16
;     movdqu oword [rsp], xmm4
;     aes_128_keygenassist 0x2, xmm4
;     aesimc xmm4, xmm4
;     sub rsp, 16
;     movdqu oword [rsp], xmm4
;     aes_128_keygenassist 0x4, xmm4
;     aesimc xmm4, xmm4
;     sub rsp, 16
;     movdqu oword [rsp], xmm4
;     aes_128_keygenassist 0x8, xmm4
;     aesimc xmm4, xmm4
;     sub rsp, 16
;     movdqu oword [rsp], xmm4
;     aes_128_keygenassist 0x10, xmm4
;     aesimc xmm4, xmm4
;     sub rsp, 16
;     movdqu oword [rsp], xmm4
;     aes_128_keygenassist 0x20, xmm4
;     aesimc xmm4, xmm4
;     sub rsp, 16
;     movdqu oword [rsp], xmm4
;     aes_128_keygenassist 0x40, xmm4
;     aesimc xmm4, xmm4
;     sub rsp, 16
;     movdqu oword [rsp], xmm4
;     aes_128_keygenassist 0x80, xmm4
;     aesimc xmm4, xmm4
;     sub rsp, 16
;     movdqu oword [rsp], xmm4
;     aes_128_keygenassist 0x1b, xmm4
;     aesimc xmm4, xmm4
;     sub rsp, 16
;     movdqu oword [rsp], xmm4
;     aes_128_keygenassist 0x36, xmm4
;     sub rsp, 16
;     movdqu oword [rsp], xmm4

; 	xor rcx, rcx

; ; Because we can't fully encrypt the .text data when it's not a 16bytes multiple - TOFIX
;     sub rdx, 16
; _aes_loop:
;     movdqu xmm1, xmm0

;     ; Load .text encrypted section block in xmm15
;     movdqu xmm7, [rax + rcx]

;     movdqu  xmm4, oword [rsp]
;     add     rsp, 16
;     pxor xmm7, xmm4 ; First xor
;     movdqu  xmm4, oword [rsp]
;     add     rsp, 16
;     aesdec xmm7, xmm4 ; Round 1
;     movdqu  xmm4, oword [rsp]
;     add     rsp, 16
;     aesdec xmm7, xmm4 ; Round 2
;     movdqu  xmm4, oword [rsp]
;     add     rsp, 16
;     aesdec xmm7, xmm4 ; Round 3
;     movdqu  xmm4, oword [rsp]
;     add     rsp, 16
;     aesdec xmm7, xmm4 ; Round 4
;     movdqu  xmm4, oword [rsp]
;     add     rsp, 16
;     aesdec xmm7, xmm4 ; Round 5
;     movdqu  xmm4, oword [rsp]
;     add     rsp, 16
;     aesdec xmm7, xmm4 ; Round 6
;     movdqu  xmm4, oword [rsp]
;     add     rsp, 16
;     aesdec xmm7, xmm4 ; Round 7
;     movdqu  xmm4, oword [rsp]
;     add     rsp, 16
;     aesdec xmm7, xmm4 ; Round 8
;     movdqu  xmm4, oword [rsp]
;     aesdec xmm7, xmm4 ; Round 9
;     aesdeclast xmm7, xmm0 ; Round 10

;     ; Load the encrypted .text section block
;     movdqu [rax + rcx], xmm7

;     ; Restore the stack for another loop
;     sub rsp, 160

;     add rcx, 16
;     cmp rdx, rcx
;     jle clean
;     jmp _aes_loop

; clean:
;     ; Reset the stack
;     add rsp, 160
;     popx rax, rdi, rsi, rsp, rdx, rcx, rbx
;     ; jmp	JUMP_ADDR
;     jmp	0xffffffff

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
    call key_expansion_128
    movdqu %2, xmm1
%endmacro

[BITS 32]

_aes_128_ecb_decrypt:
	pushx eax, edi, esi, esp, edx, ecx, ebx

	; sys_write
    call get_my_loc
    sub edx, next_i - msg
    mov ecx, edx
    mov edx, msg_len
    mov ebx, 1
    mov eax, 4
    int 0x80

    ; We save pie offset
    call get_my_loc
    sub edx, next_i - _aes_128_ecb_decrypt
    mov ebx, edx
    call get_my_loc
    sub edx, next_i - info_offset
    sub ebx, [edx]

    jmp start_unpacking

; Uses xmm1, xmm2 and xmm3
key_expansion_128:
    pshufd xmm2, xmm2, 0xff
    vpslldq xmm3, xmm1, 0x4
    pxor xmm1, xmm3
    vpslldq xmm3, xmm1, 0x4
    pxor xmm1, xmm3
    vpslldq xmm3, xmm1, 0x4
    pxor xmm1, xmm3
    pxor xmm1, xmm2
    ret

get_my_loc:
    call next_i

next_i:
    pop edx
    ret

msg	db	"[Unpacking...]", 10, 0
msg_len	equ	$ - msg

start_unpacking:
    call get_my_loc
    sub edx, next_i - info_addr
	mov	eax, [edx]
	; We add PIE offset
    add eax, ebx
    call get_my_loc
	sub edx, next_i - info_key
    movdqu xmm1, [edx]
    call get_my_loc
	sub edx, next_i - info_size
	mov	edx, [edx]

    ; Move the key in xmm0 to backup
    movdqu xmm0, xmm1

    ; We don't have enough xmm registers in x86 to store every round keys, so we push them to the stack

    ; Generating round keys

    ; 10 times
    aes_128_keygenassist 0x1, xmm4
    aesimc xmm4, xmm4
    sub esp, 16
    movdqu oword [esp], xmm4
    aes_128_keygenassist 0x2, xmm4
    aesimc xmm4, xmm4
    sub esp, 16
    movdqu oword [esp], xmm4
    aes_128_keygenassist 0x4, xmm4
    aesimc xmm4, xmm4
    sub esp, 16
    movdqu oword [esp], xmm4
    aes_128_keygenassist 0x8, xmm4
    aesimc xmm4, xmm4
    sub esp, 16
    movdqu oword [esp], xmm4
    aes_128_keygenassist 0x10, xmm4
    aesimc xmm4, xmm4
    sub esp, 16
    movdqu oword [esp], xmm4
    aes_128_keygenassist 0x20, xmm4
    aesimc xmm4, xmm4
    sub esp, 16
    movdqu oword [esp], xmm4
    aes_128_keygenassist 0x40, xmm4
    aesimc xmm4, xmm4
    sub esp, 16
    movdqu oword [esp], xmm4
    aes_128_keygenassist 0x80, xmm4
    aesimc xmm4, xmm4
    sub esp, 16
    movdqu oword [esp], xmm4
    aes_128_keygenassist 0x1b, xmm4
    aesimc xmm4, xmm4
    sub esp, 16
    movdqu oword [esp], xmm4
    aes_128_keygenassist 0x36, xmm4
    sub esp, 16
    movdqu oword [esp], xmm4

	xor ecx, ecx

; Because we can't fully encrypt the .text data when it's not a 16bytes multiple - TOFIX
    sub edx, 16
aes_loop:
    movdqu xmm1, xmm0

    ; Load .text encrypted section block in xmm15
    movdqu xmm7, [eax + ecx]

    movdqu  xmm4, oword [esp]
    add     esp, 16
    pxor xmm7, xmm4 ; First xor
    movdqu  xmm4, oword [esp]
    add     esp, 16
    aesdec xmm7, xmm4 ; Round 1
    movdqu  xmm4, oword [esp]
    add     esp, 16
    aesdec xmm7, xmm4 ; Round 2
    movdqu  xmm4, oword [esp]
    add     esp, 16
    aesdec xmm7, xmm4 ; Round 3
    movdqu  xmm4, oword [esp]
    add     esp, 16
    aesdec xmm7, xmm4 ; Round 4
    movdqu  xmm4, oword [esp]
    add     esp, 16
    aesdec xmm7, xmm4 ; Round 5
    movdqu  xmm4, oword [esp]
    add     esp, 16
    aesdec xmm7, xmm4 ; Round 6
    movdqu  xmm4, oword [esp]
    add     esp, 16
    aesdec xmm7, xmm4 ; Round 7
    movdqu  xmm4, oword [esp]
    add     esp, 16
    aesdec xmm7, xmm4 ; Round 8
    movdqu  xmm4, oword [esp]
    aesdec xmm7, xmm4 ; Round 9
    aesdeclast xmm7, xmm0 ; Round 10

    ; Load the encrypted .text section block
    movdqu [eax + ecx], xmm7

    ; Restore the stack for another loop
    sub esp, 160

    add ecx, 16
    cmp edx, ecx
    jle clean
    jmp aes_loop

clean:
    ; Reset the stack
    add esp, 160
	popx eax, edi, esi, esp, edx, ecx, ebx
    jmp	0xFFFFFFFF

; random values here, to be patched
info_start:
info_key:	    dd	0xaaaaaaaa
info_key1:	    dd	0xaaaaaaaa
info_key2:	    dd	0xaaaaaaaa
info_key3:	    dd	0xaaaaaaaa
info_addr:	    dd	0xcccccccc, 0xcccccccc ; old entry point
info_offset:    dd  0xeeeeeeee, 0xeeeeeeee ; text section offset
info_size:	    dd  0xdddddddd, 0xdddddddd ; text section size
_aes_128_ecb_decrypt_size:		dq $-_aes_128_ecb_decrypt