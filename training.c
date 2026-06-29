#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <grp.h>
#include <stdint.h> // Nécessaire pour intmax_t

int main(int argc, char *argv[])
{
  int i;
  pid_t pid;
  pid_t pgid;

  // Si aucun argument, on affiche les infos du processus courant
  if (argc == 1)
  {
    // On caste en intmax_t pour une compatibilité parfaite avec le format %jd
    fprintf(stdout, "Processus courant : %jd | Groupe : %jd\n",
            (intmax_t)getpid(), (intmax_t)getpgid(0));
    return 0;
  }

  // Boucle de traitement des arguments
  for (i = 1; i < argc; i++)
  {
    // Utilisation de long pour stocker temporairement la lecture
    long temp_pid;
    if (sscanf(argv[i], "%ld", &temp_pid) != 1)
    {
      fprintf(stderr, "PID invalide : %s\n", argv[i]);
    }
    else
    {
      pid = (pid_t)temp_pid;
      pgid = getpgid(pid);

      if (pgid == -1)
      {
        fprintf(stderr, "PID %jd inexistant ou erreur (errno: %d)\n",
                (intmax_t)pid, errno);
      }
      else
      {
        fprintf(stdout, "PID : %jd | Groupe : %jd\n",
                (intmax_t)pid, (intmax_t)pgid);
      }
    }
  }

  return 0;
}