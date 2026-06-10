/* perror() et errno */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "utilitaires.h"

int main()
{
  FILE *fp;
  char filename[80];

  printf("Indiquez un nom de fichier : ");
  lire_clavier(filename, sizeof(filename));

  if ((fp = fopen(filename, "r")) == NULL)
  {
    perror("l'ouverture du fichier a échoué !");
    printf("errno : %d.\n", errno);
    return EXIT_FAILURE;
  }
  else
  {
    puts("Fichier ouvert en lecture");
    fclose(fp);
  }

  return EXIT_SUCCESS;
}