/*
 * Exmemple d'utliosation de la fonction fgets()
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXLONG 10

int main()
{
  char buffer[MAXLONG];
  puts("Entrez une ligne de texte à la fois, ou un blanc pour sortir.");
  while (1)
  {
    fgets(buffer, MAXLONG, stdin);
    if (buffer[0] == '\n')
    {
      break;
    }

    puts(buffer);
  }

  return 0;
}