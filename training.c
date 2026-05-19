/* Démonstration de ftell() et rewind() */
#include <stdio.h>
#include <stdlib.h>

#define BUFLEN 6

char msg[] = "abcdefghijklmnopqrstuvwxyz";

int main()
{
  FILE *fp;
  char buf[BUFLEN];

  if ((fp = fopen("result.txt", "w")) == NULL)
  {
    fprintf(stderr, "Erreur à l'ouverture du fichier.");
    return 1;
  }

  if (fputs(msg, fp) == EOF)
  {
    fprintf(stderr, "Erreur à l'écriture sur le fichier...");
    return 1;
  }

  fclose(fp);
  fp = NULL;

  /* Ouvrons maintenant le fichier en lecture */
  if ((fp = fopen("result.txt", "r")) == NULL)
  {
    fprintf(stderr, "Erreur lors de la lecture du fichier");
    return 1;
  }

  printf("\nImmédiattement aprés l'ouverture, la position du curseur dans le fichier %s  est : %ld", buf, ftell(fp));

  /* Lire les 5 caractères suivants */
}