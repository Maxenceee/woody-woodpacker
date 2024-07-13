global _payload_64
extern puts

[BITS 64]

segment .text

_payload_64:
    ; Sauvegarder l'état des registres
    pushfq
    push rax
    push rbx
    push rcx
    push rdx
    push rsi
    push rdi
    push rbp
    push rsp
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15

    ; Afficher le message
    jmp .print_start_msg

.displayed_str:
    db "....WOODY....", 0x0a, 0

.print_start_msg:
    mov rax, 0x1         ; syscall: write
    mov rdi, 1           ; file descriptor: stdout
    lea rsi, [rel .displayed_str] ; message à afficher
    mov rdx, 15          ; longueur du message
    syscall

    ; Restaurer l'état des registres
    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rsp
    pop rbp
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rbx
    pop rax
    popfq

    ; Sauter à l'adresse originale (à ajuster selon votre besoin)
    jmp 0x01020304

info_start:
key:                    dq "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
encrypted_data_start:   dq 0xbbbbbbbbbbbbbbbb
encrypted_data_len:     dq 0xcccccccccccccccc
start_encode:           dq 0xdddddddddddddddd
