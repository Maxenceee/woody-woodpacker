/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   packer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:59:30 by mgama             #+#    #+#             */
/*   Updated: 2024/07/25 19:14:38 by mgama            ###   ########.fr       */
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
