#define _POSIX_C_SOURCE 200809L

#include <search.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ajoute_entree(char *francais, char *anglais)
{
    ENTRY entree;
    ENTRY *resultat;

    entree.key = strdup(francais);
    entree.data = strdup(anglais);

    if (entree.key == NULL || entree.data == NULL)
    {
        perror("strdup");
        free(entree.key);
        free(entree.data);
        exit(EXIT_FAILURE);
    }

    resultat = hsearch(entree, ENTER);

    if (resultat == NULL)
    {
        perror("hsearch (table pleine ou non initialisée)");
        // LIBÉRATION OBLIGATOIRE avant de quitter !
        free(entree.key);
        free(entree.data);
        exit(EXIT_FAILURE);
    }
}