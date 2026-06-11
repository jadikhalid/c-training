/* Utilisation de qsort() et bsearch() pour des chaines de caracteres */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utilitaires.h"

#define MAX 20

int comp(const void *s1, const void *s2)
{
  return strcmp(*(char **)s1, *(char **)s2);
}

int main()
{
  char *data[MAX], buf[80], *ptr, *key, **key1;
  int count;

  /* Entrée d'une suite de mots */
  printf("Tapez %d mots séparés par un appui sur Entrée ", MAX);
  for (count = 0; count < MAX; count++)
  {
    printf("Mot %d : ", count + 1);
    lire_clavier(buf, sizeof(buf));
    data[count] = strdup(buf);
  }

  /* Trier es mots - les pointeurs en fait */
  qsort(data, MAX, sizeof(data[0]), comp);

  /* Afficher les mots triés */
  for (count = 0; count < MAX; count++)
    printf("\n%d : %s", count + 1, data[count]);

  /* Demander une clé de recherche */
  printf("\n\nTapez une clé de recherche : ");
  lire_clavier(buf, sizeof(buf));

  /* Effectuer la recherche par clé */
  key = buf;
  key1 = &key;
  ptr = bsearch(key1, data, MAX, sizeof(data[0]), comp);

  if (ptr != NULL)
    printf("%s trouvé.\n", buf);
  else
    printf("%s non trouvé.\n", buf);

  exit(EXIT_SUCCESS);
}
