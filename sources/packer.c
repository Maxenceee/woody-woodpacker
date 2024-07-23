/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   packer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:59:30 by mgama             #+#    #+#             */
/*   Updated: 2024/07/23 18:47:53 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

size_t offset = 0;

int	write_to_file(int fd, void *data, size_t size) {
	ssize_t written = write(fd, data, size);
	if (written == -1) {
		return (-1);
	}
	offset += written;
	return (0);
}

void add_zero_padding(int fd, size_t end_offset) {
	char c = 0;

	while(offset < end_offset) {
		(void)write_to_file(fd, &c, sizeof(c));
	}
}

t_elf_section	*get_text_section(t_elf_file *elf)
{
	for (int i = 0; i < elf->e_shnum; i++) {
		if (strcmp(elf->section_tables[i].sh_name, ".text") == 0) {
			return (&elf->section_tables[i]);
		}
	}
	return (NULL);
}

int	encrypt_text_section(t_elf_file *elf)
{
	ft_verbose("\nEncrypting the `%s%s%s` section...\n", B_CYAN, ".text", RESET);
	t_elf_section	*text_section = get_text_section(elf);
	if (text_section == NULL)
		return (ft_error("The text section could not be found in the file"), -1);

	// int csize = (text_section->sh_size + text_section->sh_size % 256);
	// ft_verbose("Text section size: %d (aligned: %d)\n", text_section->sh_size, csize);
	// if (csize == 0)
	// 	return (ft_error("The text section is empty"), -1);

	// uint8_t *cypher = ft_calloc(sizeof(uint8_t), csize);
	// if (cypher == NULL)
	// 	return (ft_error("Could not allocate memory"), -1);

	// uint8_t *f_key = ft_calloc(sizeof(uint8_t), 256);
	// if (f_key == NULL)
	// 	return (ft_error("Could not allocate memory"), -1);

	// AES_256_Key_Expansion(key_aes, f_key);
	// int i = -1;
	// printf("Key expansion:\n");
	// while (f_key[++i])
	// 	printf("%02x ", f_key[i]);
	// printf("\n");

	// static const uint8_t nonce[4] = {0x00, 0xFA, 0xAC, 0x24};
	// static const uint8_t IV[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00};

	// ft_verbose("Starting encryption...\n");
	// AES_CTR_encrypt((uint8_t *)text_section->data, cypher, IV , nonce, text_section->sh_size, f_key, 64);

	// ft_memmove(text_section->data, cypher, text_section->sh_size); // copy the encrypted data in the section data buffer
	// ft_verbose("Encryption done\n");
	// free(cypher);
	// free(f_key);
	aes_128_ecb_encrypt((uint8_t *)text_section->data, text_section->sh_size, key_aes, WD_AES_KEY_SIZE);
	return (0);
}

int	packer(t_elf_file *elf)
{
	if (encrypt_text_section(elf) == -1)
		return (-1);

	ft_verbose("\nPacking the file...\n");
	int fd = open(WD_OUTPUT_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0755);
	if (fd == -1)
		return (ft_error_msg("Could not open file", WD_OUTPUT_FILE), -1);

	size_t elf_header_size = WD_ELF_HEADER_SIZE;
	size_t elf_section_header_size = WD_ELF_SECTION_HEADER_SIZE;

	(void)write_to_file(fd, elf, elf_header_size);
	add_zero_padding(fd, elf->e_phoff);

	for (int i = 0; i < elf->e_phnum; i++) {
		(void)write_to_file(fd, &elf->program_headers[i], sizeof(t_elf_program_header));
	}

	for (int i = 0; i < elf->e_shnum; i++) {
		if (elf->section_tables[i].sh_type != SHT_NOBITS)
		{
			add_zero_padding(fd, elf->section_tables[i].sh_offset);
			(void)write_to_file(fd, elf->section_tables[i].data, elf->section_tables[i].sh_size);
		}
	}

	add_zero_padding(fd, elf->e_shoff);

	for (int i = 0; i < elf->e_shnum; i++) {
		(void)write_to_file(fd, &elf->section_tables[i], elf_section_header_size);
	}

	close(fd);
	return (0);
}
