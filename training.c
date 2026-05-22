/* copie d un fichier */
#include <stdio.h>
#include <stdlib.h>
#include "utilitaires.h"

int file_copy(char *oldname, char *newname);

int main()
{
  char source[80], destination[80];

  /* Demander les noms des fichiers source et destination */

  printf("\nIndiquer le nom du fichier source : ");
  lire_clavier(source, sizeof(source));

  printf("\nIndiquee le nom du fichier destinataire : ");
  lire_clavier(destination, sizeof(destination));

  if (file_copy(source, destination) == 0)
    puts("Copie reussie");
  else
    fprintf(stderr, "Erreur au cours de la copie");

  return 1;
}

int file_copy(char *oldname, char *newname)
{
  FILE *fold, *fnew;
  char buf[BUFSIZ];
  int n;
  /* Ouverture du fichier source en mode binaire */
  if ((fold = fopen(oldname, "rb")) == NULL)
  {
    fprintf(stderr, "Erreur lors de l ouverture du fichier %s\n", oldname);
    return 1;
  }
  /* Ouverture du fichier destination en ecriture
  en mode binaire */
  if ((fnew = fopen(newname, "wb")) == NULL)
  {
    fclose(fold);
    return 1;
  }
  /* Lire le fichier source morceaux par morceaux.
  Si on n a pas atteint la fin du fichier , ercrire les
  donnees sur le fichier destination */
}