# Woody Woodpacker

Our Woody Woodpacker projet for the 42 School cursus. The projet is a binary packer made in C, which is a tool that takes a binary file and encrypts it in a way that it can decrypt itself at runtime. This program can be used to obfuscate a binary.

Final grade : `125/100` & Outstanding Project

## Getting started

You need to compile the project with `make`.

### Usage
```sh
usage: woody_woodpacker <option(s)> file
  Options are:
  -h, --file-header        Display the ELF file header
  -l, --segments           Display the program headers
  -S, --sections           Display the sections\' header
  -s, --symbols            Display the symbol table
  -d, --data               Display the section data
  -g, --update-syms        Update debug symbols
  -k, --key=<key-val|@file_path> Use custom encrypt key (16 bytes)
  -v, --verbose            Verbose mode
  -V, --version            Print version
  -n, --no-pack            Do not pack the file
```

## Basic concept

A packer is a type of software used to compress and encrypt executable files. The primary goal of this tool is to obfuscate the contents of a binary, making it harder to analyze or reverse-engineer. The program works by taking an input binary file and injecting decryption code into it during the packing process. When the packed binary is executed, the injected code runs first to decrypt the original content before handing over control to the original program. This ensures that while the binary is stored and transferred in an encrypted state, it can still execute normally when run. This process enhances security by protecting the binary from tampering and unauthorized access.

### Overview

The process of packing a binary involves several key steps to ensure the binary is properly encrypted and can execute normally. The main steps are as follows:
1. **Read and verify the binary**: The input binary file is read into memory and its content is parsed to extract the necessary information, such as the ELF header, program headers, and section headers.
2. **Search for a loadable segment**: A loadable segment in the binary is searched for, where modifications can be safely made.
3. **Find the last section in the segment**: Within the found segment, the last section is identified to determine where to inject the new code.
4. **Create a new section**: A new section is created to contain the injected decryption code. This involves:
	- Specifying various parameters for the new section, such as name, type, flags, and size.
	- Calculating the address and offset for the new section.
	- Copying the decryption payload into the new section.
	- Updating the section string table to include the new section name.
	- Increasing the number of entries in the section header table.
5. **Update the segment**: The segment containing the new section is updated to reflect the changes made. This includes:
	- Increasing the size of the segment to accommodate the new section.
	- Updating the segment's memory mapping to include the new section.
6. **Adjust addresses and offsets**: The addresses and offsets of the sections following the new section are adjusted to account for the new section.
7. **Update the entry point**: The program's entry point is modified to point to the new decryption code, ensuring it runs first when the binary is executed.
8. **Encrypt the .text section**: The .text section of the binary is encrypted using the [AES algorithm](https://fr.wikipedia.org/wiki/Advanced_Encryption_Standard) to protect the executable code.
8. **Write the final file**: The modified binary, now containing the injected decryption code, is written to the output file.