/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_payload.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:42:13 by mgama             #+#    #+#             */
/*   Updated: 2024/05/14 12:12:13 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// Structure du header ELF
typedef struct {
    uint8_t e_ident[16];
    uint16_t e_type;
    uint16_t e_machine;
    uint32_t e_version;
    uint64_t e_entry;
    uint64_t e_phoff;
    uint64_t e_shoff;
    uint32_t e_flags;
    uint16_t e_ehsize;
    uint16_t e_phentsize;
    uint16_t e_phnum;
    uint16_t e_shentsize;
    uint16_t e_shnum;
    uint16_t e_shstrndx;
} Elf64_Ehdr;

// Structure des headers de section
typedef struct {
    uint32_t sh_name;
    uint32_t sh_type;
    uint64_t sh_flags;
    uint64_t sh_addr;
    uint64_t sh_offset;
    uint64_t sh_size;
    uint32_t sh_link;
    uint32_t sh_info;
    uint64_t sh_addralign;
    uint64_t sh_entsize;
} Elf64_Shdr;

// Structure des headers de programme
typedef struct {
    uint32_t p_type;
    uint32_t p_flags;
    uint64_t p_offset;
    uint64_t p_vaddr;
    uint64_t p_paddr;
    uint64_t p_filesz;
    uint64_t p_memsz;
    uint64_t p_align;
} Elf64_Phdr;

const uint8_t code[] = {
	0x48, 0xC7, 0xC0, 0x01, 0x00, 0x00, 0x00, // mov rax, 0x1
	0x48, 0xC7, 0xC7, 0x01, 0x00, 0x00, 0x00, // mov rdi, 0x1
	0x48, 0x8D, 0x35, 0x0E, 0x00, 0x00, 0x00, // lea rsi, [rip + 0xE]
	0xBA, 0x0F, 0x00, 0x00, 0x00,             // mov edx, 0xF
	0x0F, 0x05,                               // syscall
	0xC3                                      // ret
};

// int main() {
//     // Initialiser le header ELF
//     Elf64_Ehdr ehdr;
//     memset(&ehdr, 0, sizeof(Elf64_Ehdr));
//     ehdr.e_ident[0] = 0x7f;
//     ehdr.e_ident[1] = 'E';
//     ehdr.e_ident[2] = 'L';
//     ehdr.e_ident[3] = 'F';
//     ehdr.e_ident[4] = 2; // 64-bit
//     ehdr.e_type = 2; // Executable file
//     ehdr.e_machine = 0x3e; // AMD64
//     ehdr.e_version = 1; // ELF version
//     ehdr.e_entry = 0x400078; // Adresse de début du code
//     ehdr.e_phoff = sizeof(Elf64_Ehdr); // Offset des headers de programme

//     // Initialiser le header de section .text
//     Elf64_Shdr text_shdr;
//     memset(&text_shdr, 0, sizeof(Elf64_Shdr));
//     text_shdr.sh_name = 1; // Nom de la section
//     text_shdr.sh_type = 1; // Type de la section (SHT_PROGBITS)
//     text_shdr.sh_flags = 6; // Flags de la section (SHF_ALLOC | SHF_EXECINSTR)
//     text_shdr.sh_size = 35; // Taille du code
//     text_shdr.sh_addralign = 16; // Alignement

//     // Initialiser le header de section .shstrtab
//     Elf64_Shdr shstrtab_shdr;
//     memset(&shstrtab_shdr, 0, sizeof(Elf64_Shdr));
//     shstrtab_shdr.sh_type = 3; // Type de la section (SHT_STRTAB)
//     shstrtab_shdr.sh_addralign = 1; // Alignement

//     // Initialiser le header de section de table d'en-têtes de section
//     Elf64_Shdr shdr_shdr;
//     memset(&shdr_shdr, 0, sizeof(Elf64_Shdr));
//     shdr_shdr.sh_type = 9; // Type de la section (SHT_STRTAB)
//     shdr_shdr.sh_addralign = 8; // Alignement

//     // Ouvrir le fichier ELF
//     FILE *file = fopen("output.elf", "wb");
//     if (!file) {
//         perror("Erreur lors de l'ouverture du fichier");
//         return 1;
//     }

//     // Écrire le header ELF
//     fwrite(&ehdr, sizeof(Elf64_Ehdr), 1, file);

//     // Calculer la taille du nom de la section .shstrtab
//     size_t shstrtab_size = strlen(".text") + 1; // +1 pour le zéro de terminaison
//     shstrtab_size += strlen(".shstrtab") + 1;

//     // Écrire les en-têtes de section
//     text_shdr.sh_offset = sizeof(Elf64_Ehdr); // Offset de la section .text
//     fwrite(&text_shdr, sizeof(Elf64_Shdr), 1, file);

//     shstrtab_shdr.sh_offset = sizeof(Elf64_Ehdr) + sizeof(Elf64_Shdr); // Offset de la section .shstrtab
//     shstrtab_shdr.sh_size = shstrtab_size;
//     fwrite(&shstrtab_shdr, sizeof(Elf64_Shdr), 1, file);

//     shdr_shdr.sh_offset = sizeof(Elf64_Ehdr) + sizeof(Elf64_Shdr) * 2; // Offset de la section de table d'en-têtes de section
//     fwrite(&shdr_shdr, sizeof(Elf64_Shdr), 1, file);

//     // Écrire les noms des sections dans la section .shstrtab
//     fwrite(".text\0.shstrtab\0", shstrtab_size, 1, file);

//     // Écrire le code dans le fichier ELF
//     unsigned char code[] = {
//         0x48, 0xC7, 0xC0, 0x01, 0x00, 0x00, 0x00, // mov rax, 0x1
//         0x48, 0xC7, 0xC7, 0x01, 0x00, 0x00, 0x00, // mov rdi, 0x1
//         0x48, 0x8D, 0x35, 0x0E, 0x00, 0x00, 0x00, // lea rsi, [rip + 0xE]
//         0xBA, 0x0F, 0x00, 0x00, 0x00,             // mov edx, 0xF
//         0x0F, 0x05,                               // syscall
//         0xC3                                      // ret
//     };

//     // Écrire le code dans le fichier ELF
//     fwrite(code, sizeof(code), 1, file);

//     // Fermer le fichier ELF
//     fclose(file);

//     printf("Fichier ELF généré avec succès!\n");

//     return 0;
// }
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#define HEAP_STRING_IMPL
#include "heap_string.h"

//https://en.wikipedia.org/wiki/Executable_and_Linkable_Format
//http://www.muppetlabs.com/~breadbox/software/tiny/teensy.html
// Making some assumptions
// Little endian (LE)
// i386/x86
// Also making use of a small vector / array like container structure
// Which can be found here https://github.com/riicchhaarrd/rhd

typedef uint8_t u8;

void dd(heap_string *s, uint32_t i)
{
    union
    {
	uint32_t i;
	uint8_t b[4];
    } u = { .i = i };
    
    for(size_t i = 0; i < 4; ++i)
	heap_string_push(s, u.b[i]);
}

void dw(heap_string *s, uint16_t i)
{
    union
    {
	uint16_t s;
	uint8_t b[2];
    } u = { .s = i };

    heap_string_push(s, u.b[0]);
    heap_string_push(s, u.b[1]);
}

void db(heap_string *s, u8 op)
{
    heap_string_push(s, op);
}

void buf(heap_string *s, const char *buf, size_t len)
{
    for(size_t i = 0; i < len; ++i)
    {
	heap_string_push(s, buf[i] & 0xff);
    }
}

int main()
{
    heap_string image = NULL;
    db(&image, 0x7f);
    db(&image, 'E');
    db(&image, 'L');
    db(&image, 'F');
    db(&image, 1);
    db(&image, 1);
    db(&image, 1);
    db(&image, 0);

    for(size_t i = 0; i < 8; ++i)
	    db(&image, 0);
    dw(&image, 2); //e_type
    dw(&image, 3); //e_machine
    dd(&image, 1); //e_version

    size_t entry_offset = heap_string_size(&image);
    dd(&image, 0); //we'll fill this in later //e_entry
    
    size_t ph_offset = heap_string_size(&image);
    dd(&image, 0); //we'll fill this in later //e_phoff

    dd(&image, 0); //e_shoff

    dd(&image, 0); //e_flags
    
    size_t ehsize_offset = heap_string_size(&image);
    dw(&image, 0); //we'll fill this in later //e_ehsize

    size_t phentsize_offset = heap_string_size(&image);
    dw(&image, 0); //we'll fill this in later //e_phentsize

    dw(&image, 1); //e_phnum
    dw(&image, 0); //e_shentsize
    dw(&image, 0); //e_shnum
    dw(&image, 0); //e_shstrndx

    //fill in some known values now
    *(uint16_t*)(image + ehsize_offset) = heap_string_size(&image);

    int phdr_offset = heap_string_size(&image);
    *(uint16_t*)(image + ph_offset) = phdr_offset;
    
    uint32_t org = 0x08048000;

    dd(&image, 1); //p_type
    dd(&image, 0); //p_offset
    dd(&image, org); //p_vaddr
    dd(&image, org); //p_paddr

    size_t filesz_offset = heap_string_size(&image);
    dd(&image, 0); //p_filesz

    size_t memsz_offset = heap_string_size(&image);
    dd(&image, 0); //p_memsz

    dd(&image, 5); //p_flags
    dd(&image, 0x1000); //p_align

    //fill in some more known values
    
    int phentsize = heap_string_size(&image) - phdr_offset;
    *(uint16_t*)(image + phentsize_offset) = phentsize;

    size_t entry = heap_string_size(&image);
    *(uint32_t*)(image + entry_offset) = entry + org;

    //append opcodes here for the program
    
    db(&image, 0x31); db(&image, 0xc0); //xor eax,eax
    db(&image, 0xb0); //mov al, 4
    db(&image, 0x04);
    
    static const char *message = "Hello world!\n";
    //got lazy writing every opcode inside emit calls
    buf(&image, "\xbb\x01\x00\x00\x00", 5); //mov ebx, 1 //set arg0 to fd STDOUT
    db(&image, 0xb9); //mov ecx, imm32
    size_t message_ref_offset = heap_string_size(&image);
    dd(&image, 0); //we'll fill this in later
    buf(&image, "\xba\x0e\x00\x00\x00", 5); //mov edx,14 //fixed size of Hello World!\n + '\0'
    //cba to do any lda, or mov edx,[reg]
    db(&image, 0xcd); //int 0x80
    db(&image, 0x80);
    
    db(&image, 0xb3); //mov bl,42
    db(&image, 0x2a);
    db(&image, 0x31); //xor eax,eax
    db(&image, 0xc0);
    db(&image, 0x40); //inc eax
    db(&image, 0xcd); //int 0x80
    db(&image, 0x80);

    //this code won't ever be reached, let's just put our data here for now
    //write our string here
    *(uint32_t*)(image + message_ref_offset) = heap_string_size(&image) + org;
    buf(&image, message, strlen(message) + 1);

    size_t filesize = heap_string_size(&image);
    *(uint32_t*)(image + filesz_offset) = filesize;
    *(uint32_t*)(image + memsz_offset) = filesize;

    FILE * fp = fopen("test.elf", "wb");
    if(!fp) return 0;
    fwrite(image, filesize, 1, fp);
    fclose(fp);

    //Make sure output is executable (chmod +x <file>)
    //usage: gcc elf.c && ./a.out && ./test.elf

    heap_string_free(&image);
    return 0;
}