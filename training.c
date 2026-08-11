#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>

#define TAILLE_CHAINE 128

void *mon_malloc_avec_mmap(size_t taille)
{
    void *retour;
    retour = mmap(NULL, taille, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
    if (retour == MAP_FAILED)
    {
        perror("mmap");
        return NULL;
    }
    return retour;
}

int main(void)
{
    char *chaine = NULL;
    fprintf(stdout, "Allocation de %d octets \n", TAILLE_CHAINE);
    chaine = mon_malloc_avec_mmap(TAILLE_CHAINE);
    if (chaine == NULL)
    {
        perror("mmap");
        exit(1);
    }
    fprintf(stdout, "Protections par défaut \n");
    fprintf(stdout, "Ecriture...");
    strcpy(chaine, "ok");
    fprintf(stdout, "ok\n");
    fprintf(stdout, "Lecture...");
    fprintf(stdout, "%s\n", chaine);
    fprintf(stdout, "Interdiction d'écriture \n");

    if (mprotect(chaine, TAILLE_CHAINE, PROT_READ) < 0)
    {
        perror("mprotect");
        exit(1);
    }

    fprintf(stdout, "Lecture ...\n");
    fprintf(stdout, "%s\n", chaine);
    fprintf(stdout, "Ecritue...");
    strcpy(chaine, "Non");

    return 0;
}
