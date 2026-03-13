/*perroquet.c : ce programme repete ce qu'il vient de lire au clavier*/
#include <stdlib.h>
#include <stdio.h>

int lire_clavier(char *str, int taille)
{
  int i;
  fgets(str, taille, stdin);
  str[taille - 1] = '\0';
  for (i = 0; str[i]; i++)
  {
    if (str[i] == '\n')
    {
      /* code */
      str[i] = '\0';
      break;
    }
  }
  return i;
}