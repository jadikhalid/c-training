#include <stdio.h>
#include <stdlib.h>

int main()
{
  FILE *f = fopen("test.txt", "r");
  if (f == NULL)
  {
    perror("Erreure d'ouverture de fichier");
    return 1;
  }
  long long occurences[256] = {0};
  int c;

  while ((c = fgetc(f)) != EOF)
    occurences[(unsigned char)c]++;

  fclose(f);

  printf("Statistique des caracteres :\n");
  for (int i = 0; i < 256; i++)
  {
    if (occurences[i] > 0)
    {
      // On affiche le caractère (si imprimable) et son nombre
      if (i > 31 && i < 127)
      {
        printf("'%c' : %lld\n", i, occurences[i]);
      }
      else
      {
        printf("Code ASCII %d : %lld\n", i, occurences[i]);
      }
    }
  }
}
