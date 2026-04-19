/*
 * Exemple de l'utilisation de l'instruction continue
 */

#include <stdio.h>
#include <stdlib.h>
#include "utilitaires.h"

int main()
{
  char buffer[81];
  int ctr = 10;

  puts("Entrez une ligne de texte :");
  lire_clavier(buffer, sizeof(buffer));

  for (ctr = 0; buffer[ctr] != '\0'; ctr++)
  {
    if (buffer[ctr] == 'a' || buffer[ctr] == 'e' || buffer[ctr] == 'i' || buffer[ctr] == 'u' || buffer[ctr] == 'o')
      continue;

    putchar(buffer[ctr]);
  }
  printf("\n");
  return 0;
}