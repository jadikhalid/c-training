/* List_it.c ce programme affiche du code source avec
les numéros de lignes. */

#include <stdio.h>
#include <stdlib.h>
#include "utilitaires.h"

void display_usage(void);

int line;

int main(int argc, char *argv[])
{
  char buffer[256];
  FILE *fp;
  if (argc < 2)
  {
    display_usage();
    exit(EXIT_FAILURE);
  }
  if ((fp = fopen(argv[1], "r")) == NULL)
  {
    fprintf(stderr, "erreur fichier, %s!", argv[1]);
    exit(EXIT_FAILURE);
  }
  line = 1;

  while (fgets(buffer, sizeof(buffer), fp) != NULL)
    fprintf(stdout, "%4d:\t%s", line++, buffer);
  fclose(fp);
  exit(EXIT_SUCCESS);
}

void display_usage(void)
{
  fprintf(stderr, "La syntaxe est la suivante :\n\n");
  fprintf(stderr, "list_it filename.ext\n");
}
