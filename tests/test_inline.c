/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_inline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:56:11 by mgama             #+#    #+#             */
/*   Updated: 2024/05/15 18:38:04 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdio.h>
#include <sys/mman.h>
#include <string.h>

// extern uint64_t randomfunction_size;

static inline int randomfunction2()
{
	int a = 10;
	int b = 2;
	int c = 4;
	int d = 6;

	return (a + b) * c - d;
}

int randomfunction()
{
	int a = randomfunction2();
	return a;
}

int main(int argc, char const *argv[])
{
	size_t function_size = (size_t)((char *)main - (char *)randomfunction);
	printf("Function addr: %p\n", randomfunction);
	printf("Function size: %zu\n", function_size);

    // Aligner la taille sur la taille d'une page mémoire
    size_t pagesize = (size_t)(4096);
    size_t alloc_size = (function_size + pagesize - 1) & ~(pagesize - 1);

    // Allouer de la mémoire pour la copie de la fonction, avec les permissions appropriées
    void *copy = mmap(NULL, alloc_size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (copy == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    // Copier le code machine de la fonction originale vers la nouvelle région de mémoire
    memcpy(copy, (void *)randomfunction, function_size);

    // Exécuter la fonction copiée
    int (*copied_function)() = (int (*)())copy;
	printf("Copied function: %p => %d\n", copied_function, copied_function());

    // Libérer la mémoire allouée
    if (munmap(copy, alloc_size) == -1) {
        perror("munmap");
        return 1;
    }
	return 0;
}
