# Woody Woodpacker

Our Woody Woodpacker projet for the 42 School cursus. The projet is a binary packer made in C, which is a tool that takes a binary file and encrypts it in a way that it can decrypt itself at runtime. 

Final grade : `125/100` & Outstanding Project

## Getting started

You need to compile the project with `make`.

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
```
