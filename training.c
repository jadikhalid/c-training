/* Lecture de données formqtées sur un fichier avec fscanf() */
#include <stdlib.h>
#include <stdio.h>

int main()
{
  float f1, f2, f3, f4, f5;
  FILE *fp;

  if ((fp = fopen("result.txt", "r")) == NULL)
  {
    fprintf(stderr, "Erreur à l'ouverture du fichier.\n");
    return 1;
  }
  fscanf(fp, "%f %f %f %f %f", &f1, &f2, &f3, &f4, &f5);
  printf("Les valeurs sont : %f, %f, %f, %f et %f.\n ", f1, f2, f3, f4, f5);

  fclose(fp);
  fp = NULL;

  return 0;
}