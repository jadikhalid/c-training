/* Démonstration de la fonction fopen() */
#include <stdio.h>
#include <stdlib.h>
#include "utilitaires.h"

int main()
{
  FILE *fp;
  char filename[40], mode[4];

  while (1)
  {
    /* Indiquer le nom de fichier et le mode */
    printf("\nTapez un nom de fichier : ");
    lire_clavier(filename, sizeof(filename));
    printf("\nTapez un mode , 3 caracteres au plus : ");
    lire_clavier(mode, sizeof(mode));

    /* Essayer d'ouvrir le fichier */

    if ((fp = fopen(filename, mode)) != NULL)
    {
      printf("\nOUverture réussie %s en mode %s.\n", filename, mode);
      fclose(fp);
      puts("Tapez x pour terminer, ou n'importe quoi d'autres pour continuer");
      if (getc(stdin) == 'x')
        break;
      else
        continue;
    }
    else
    {
      fprintf(stderr, "\nErreur a l'ouverture du fichier %s en mode %s.", filename, mode);
      puts("Tapez x pour termine, ou n'importe quoi d'autres pour réessayer");
      if (getc(stdin) == 'x')
        break;
      else
        continue;
    }
  }

  return 0;
}