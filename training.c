/* Demonstration de la fonction fprintf() */
#include <stdlib.h>
#include <stdio.h>
#include "utilitaires.h"

void clear_kb(void);

int main()
{
  FILE *fp;
  float data[5];
  int count;
  char filename[20];

  puts("Tapez 5 valeurs numériques en flottant.");

  for (count = 0; count < 5; count++)
    scanf("%f", &data[count]);

  clear_kb();

  puts("Indiquez un nom pour le fichier.");
  lire_clavier(filename, sizeof(filename));

  if ((fp = fopen(filename, "w")) == NULL)
  {
    fprintf(stderr, "Erreur a l'ouverture du fichier %s.", filename);
    return 1;
  }

  for (count = 0; count < 5; count++)
  {
    fprintf(fp, "data[%d] = %f\n", count, data[count]);
    fprintf(stdout, "data[%d] = %f\n", count, data[count]);
  }
  fclose(fp);
  return 0;
}

void clear_kb(void)
{
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}