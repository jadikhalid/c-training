/*
 * Illustration de la fonction system()
 */

#include <stdio.h>
#include <stdlib.h>
#include "utilitaires.h"

int main()
{
  char input[40];

  while (1)
  {
    puts("\nEntrez une commande systeme, ou une ligne blanche pour sortir");
    lire_clavier(input, sizeof(input));
  }
}