#include <stdio.h>

int main()
{
  FILE *fp;
  if ((fp = fopen("resultat.txt", "r")) == NULL)
  {
    fprintf(stderr, "Erreur de la lecture du fichier");
    return -1;
  }
  int c;
  while ((c = fgetc(fp)) != EOF)
    fputc(c, stdout);

  fclose(fp);

  return 0;
}