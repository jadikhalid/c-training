/* Démonstration de strcpy() */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char source[] = "Une chaine de caracteres.";

int main()
{
  char dest1[80];
  char *dest2;

  printf("\nsource : %s", source);

  /* Copier cers dest1 */
  strcpy(dest1, source);
  printf("\ndest1 : %s", dest1);

  /* Copier vers dest2 */
  dest2 = malloc(strlen(source) + 1);
  strcpy(dest2, source);
  printf("\ndest2 : %s", dest2);

  return 0;
}