#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LG_MAXI 256

int main(void)
{
    char *ligne;
    char *champs;
    int l, c;

    if ((ligne = (char *)malloc(LG_MAXI)) == NULL)
    {
        perror("malloc");
        exit(1);
    }

    l = 1;

    // Boucle sur chaque ligne de stdin
    while (fgets(ligne, LG_MAXI, stdin) != NULL)
    {
        fprintf(stdout, "--- Ligne %d ---\n", l);
        c = 1;

        // Premier appel à strtok sur la ligne
        champs = strtok(ligne, " \t\r\n");

        // Boucle sur chaque mot/champ de la ligne
        while (champs != NULL)
        {
            printf("  Champ %d : %s\n", c, champs);
            c++;
            // Appels suivants avec NULL
            champs = strtok(NULL, " \t\r\n");
        }

        l++; // Incrémentation correcte après chaque ligne
    }

    free(ligne); // Bonne pratique : libérer la mémoire
    return 0;
}