#include "utilitaires.h"

int lire_clavier(char *str, int taille)
{
  int i;
  if (fgets(str, taille, stdin) != NULL)
  {
    // 1. On cherche le \n pour le supprimer
    for (i = 0; str[i] != '\0'; i++)
    {
      if (str[i] == '\n')
      {
        str[i] = '\0';
        return i; // On a trouvé le \n, tout est propre, on sort.
      }
    }

    // 2. Si on arrive ici, c'est que le \n n'était PAS dans le buffer.
    // La ligne était trop longue ! Il faut vider le surplus de stdin.
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
      ;

    return i; // i contient ici la taille max du buffer - 1
  }
  return 0;
}