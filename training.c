#define _DEFAULT_SOURCE /* See feature_test_macros(7) */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <grp.h>

int main(int argc, char *argv[])
{
  gid_t *table_gid = NULL;
  int i;
  // int taille;

  if (argc < 2)
  {
    fprintf(stderr, "Usage %s GID ...\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  if ((table_gid = calloc((size_t)(argc - 1), sizeof(gid_t))) == NULL)
  {
    fprintf(stderr, "Erreur calloc, errno = %d\n", errno);
    exit(EXIT_FAILURE);
  }
  for (i = 1; i < argc; i++)
    if (sscanf(argv[i], "%u", &(table_gid[i - 1])) != 1)
    {
      fprintf(stderr, "GID invalide : %s\n", argv[i]);
      exit(EXIT_FAILURE);
    }

  return 0;
}