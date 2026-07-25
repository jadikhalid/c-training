#include <stdio.h>
#include <ctype.h>

int main(void)
{
  int lu;
  char caracteres[17];
  int emplacement = 0;
  int rang = 0;

  // Initialisation propre du tableau
  for (int i = 0; i < 17; i++)
    caracteres[i] = '\0';

  while ((lu = getchar()) != EOF)
  {
    rang = emplacement % 16;

    if (rang == 0)
    {
      fprintf(stdout, "%08x  ", emplacement);
      fflush(stdout);
    }

    fprintf(stdout, "%02x", lu);
    fflush(stdout);

    if (rang == 7)
      fprintf(stdout, "-");
    else
      fprintf(stdout, " ");

    if (isprint(lu))
      caracteres[rang] = (char)lu;
    else
      caracteres[rang] = '.';

    if (rang == 15)
    {
      fprintf(stdout, " |%s|\n", caracteres);
      fflush(stdout); // On force l'écriture immédiate
    }

    emplacement++;
  }

  // Si le fichier se termine et que la dernière ligne est incomplète
  if (rang != 15 && emplacement > 0)
  {
    int i = rang + 1;
    while (i < 16)
    {
      fprintf(stdout, "   ");
      caracteres[i] = ' ';
      i++;
    }
    caracteres[16] = '\0';
    fprintf(stdout, " |%s|\n", caracteres);
    fflush(stdout);
  }

  return 0;
}