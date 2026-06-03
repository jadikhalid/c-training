/* Démonstration de strtod() */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "utilitaires.h"

int main()
{
  char buf[80];
  double d;

  while (1)
  {
    printf("\nTapez la chaine de caracteres a convertir"
           "(Entrée pour terminer):");
    lire_clavier(buf, sizeof(buf));

    if (strlen(buf) == 0)
    {
      printf("Aucun caracteres de renseigné ! Bye !");
      break;
    }

    errno = 0;
    d = strtod(buf, NULL);

    if (errno)
      printf("Pas de valeur a convertir dans la chaine\n");
    else
    {
      printf("Valeur convertie : %lf.", d);
      break;
    }
  }

  return 0;
}