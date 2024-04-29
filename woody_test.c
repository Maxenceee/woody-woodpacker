#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include "elf.h"

int main() {
    // Ouvrir le fichier ELF chiffré en lecture
    int fd = open("fichier", O_RDONLY);
    if (fd == -1) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    // Obtenir la taille du fichier
    off_t taille_fichier = lseek(fd, 0, SEEK_END);
    if (taille_fichier == -1) {
        perror("Erreur lors de la détermination de la taille du fichier");
        close(fd);
        return 1;
    }

    // Revenir au début du fichier
    if (lseek(fd, 0, SEEK_SET) == -1) {
        perror("Erreur lors du retour au début du fichier");
        close(fd);
        return 1;
    }

    // Allouer de la mémoire pour stocker les données du fichier
    void *donnees_chiffrees = malloc(taille_fichier);
    if (!donnees_chiffrees) {
        perror("Erreur lors de l'allocation de mémoire pour les données chiffrées");
        close(fd);
        return 1;
    }

    // Lire les données du fichier
    ssize_t bytes_lus = read(fd, donnees_chiffrees, taille_fichier);
    if (bytes_lus != taille_fichier) {
        perror("Erreur lors de la lecture du fichier");
        close(fd);
        free(donnees_chiffrees);
        return 1;
    }

    // Fermer le fichier
    close(fd);

    // Charger les données déchiffrées en mémoire avec autorisations d'exécution
    void *adresse_debut_page = mmap(NULL, taille_fichier, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (adresse_debut_page == MAP_FAILED) {
        perror("Erreur lors du chargement des données en mémoire");
        free(donnees_chiffrees);
        return 1;
    }

    // Copier les données déchiffrées dans la mémoire allouée
    memcpy(adresse_debut_page, donnees_chiffrees, taille_fichier);

	// Autoriser l'exécution du code en mémoire
    if (mprotect(adresse_debut_page, taille_fichier, PROT_READ | PROT_EXEC) == -1) {
        perror("Erreur lors de la modification des autorisations de mémoire");
        munmap(adresse_debut_page, taille_fichier);
        free(donnees_chiffrees);
        return 1;
    }

    // Exécuter le code en lançant le pointeur vers le point d'entrée du programme
    Elf64_Ehdr *entete_elf = (Elf64_Ehdr *)donnees_chiffrees;
    Elf64_Addr offset_point_entree = entete_elf->e_entry;

    void *adresse_memoire = adresse_debut_page + offset_point_entree;
    void (*entry_point)() = (void (*)())(adresse_memoire);
	printf("%p\n", entry_point);
	printf("...Woody...\n");
    entry_point();

    // Libérer la mémoire utilisée
    munmap(adresse_memoire, taille_fichier);
    free(donnees_chiffrees);

    return 0;
}
