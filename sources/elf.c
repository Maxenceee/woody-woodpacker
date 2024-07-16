/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:57:34 by mgama             #+#    #+#             */
/*   Updated: 2024/07/16 14:58:03 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elf.h"

const char *g_elf_section_table_type[] = {
	"NULL",
	"PROGBITS",
	"SYMTAB",
	"STRTAB",
	"RELA",
	"HASH",
	"DYNAMIC",
	"NOTE",
	"NOBITS",
	"REL",
	"SHLIB",
	"DYNSYM",
	"INIT_ARRAY",
	"FINI_ARRAY",
	"PREINIT_ARRAY",
	"GROUP",
	"SYMTAB_SHNDX",
	"NUM"
};

const char *g_elf_osabi_name[] = {
	"UNIX - System V",
	"HP-UX",
	"NetBSD",
	"Linux",
	"GNU Hurd",
	"Solaris",
	"AIX (Monterey)",
	"IRIX",
	"FreeBSD",
	"Tru64",
	"Novell Modesto",
	"OpenBSD",
	"OpenVMS",
	"NonStop Kernel",
	"AROS",
	"FenixOS",
	"Nuxi CloudABI",
	"Stratus Technologies OpenVOS"
};

const char *g_elf_program_header_type[] = {
	"NULL",
	"LOAD",
	"DYNAMIC",
	"INTERP",
	"NOTE",
	"SHLIB",
	"PHDR",
	"TLS",
	"NUM",
	"LOOS",
	"GNU_EH_FRAME",
	"GNU_STACK",
	"GNU_RELRO",
	"LOSUNW",
	"SUNWBSS",
	"SUNWSTACK",
	"HIOS",
	"LOPROC",
	"HIPROC"
};