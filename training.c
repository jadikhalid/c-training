/* Compte le nombre d'occurences de chaque caractère dans un fichier. */

#include <stdio.h>
#include <stdlib.h>
#include "utilitaires.h"

int file_exists(char *filename);

int main()
{
  char ch, source[80];
  int index;
  long count[127];

  FILE *fp;

  /* Lecture des noms de fichiers source et destination */
  printf("\nEntrez le nom du fichier source : ");
  lire_clavier(source, sizeof(source));

  /* Contôle de l'existence du fichier source */
  if (!file_exists(source))
  {
    fprintf(stderr, "Le fichier source ne s'ouvre pas ! problème du fichier ou non exitencde du fichier.");
    return 1;
  }

  /* Ouverture du fichier */
  if ((fp = fopen(source, "r")) == NULL)
  {
    fprintf(stderr, "Erreur lors de l'ouverture du fichier source.");
    return 1;
  }

  /* Initialisation des éléments du tableau */
  for (index = 0; index < 127; index++)
    count[index] = 0;

  while ((ch = fgetc(fp)) != EOF)
  {
    if (ch > 31 && ch < 127)
      count[(int)ch]++;
  }

  /* Affichage des résultats */
  for (index = 32; index < 127; index++)
  {
    if (count[index] != 0)
      printf("%c - %ld\n", index, count[index]);
  }

  fclose(fp);

  return 0;
}

int file_exists(char *filename)
{
  /* Renvoie TRUE si le fichier texte existe, sinon FALSE */
  FILE *fp;
  if ((fp = fopen(filename, "r")) == NULL)
    return 0;
  else
  {
    fclose(fp);
    return 1;
  }
}