/* Demonstration de noms de fichier temporaires */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  char *buffer;
  int fd;
  FILE *tmpfd;

  /* Garnir le buffer avec un nom de fichier temporaire */

  buffer = strdup("fichier_XXXXXX");

  /* Crée le fichier temporaire */

  if ((fd = mkstemp(buffer)) == -1)
  {
    fprintf(stderr, "Impossible de créer le fichier.\n");
    return 1;
  }
  if ((tmpfd = fdopen(fd, "wb")) == NULL)
  {
    fprintf(stderr, "Erreur lors de l ouverture du fichier");
    return 1;
  }

  /* Utiliser le fichier temporaire */
  printf("Nom de fichier temporaire : %s", buffer);

  fclose(tmpfd);
  free(buffer);

  return 0;
}