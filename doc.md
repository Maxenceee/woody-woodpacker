# Genaral

allowed function : 
* open, close, exit
* fpusts, fflush, lseek
* mmap, munmap, mprotect
* perror, strerror
* syscall
* the functions of the printf family
* the function authorized within your libft (read, write, malloc, free, for examaple)
  * any for the bonus, must be justified during the eval	

objectif : 
* The goal of this project is to code a program that will at first encrypt a program given
as parameter. Only 64 bits ELF files will be managed here.
* A new program called woody will be generated from this execution. When this new
program (woody) will be executed, it will have to be decrypted to be run. Its execution
has to be totally identical to the program given as parameter in the last step.

other : 
* excutable name : woody_woodpacker
* bonus :
  * 32bits management.
  * Parameterized key.
  * Optimisation of the used algorithm through assembly language.
  * Additional binary management (PE, Mach-O..)
  * Binary compression.
  * **any other interesting thing can be implemented ??**

step :
* look if file is here/openable/permission with open --> return false if wrong
* look if ELF64.
	* header of ELF64: 7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00
  * mafic number: 0x7F 'E' 'L' 'F'
* parse the executable
	* extract the section
	* compress the session
* encript and conpress the file with the algo
	* custom key of encription : 9c090817c68464c4f153ecda9afce135951de141
*	create a main that decrypt and run the executable

# Usefull

https://en.wikipedia.org/wiki/Executable_and_Linkable_Format#