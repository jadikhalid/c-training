#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>
#include <unistd.h>

sigjmp_buf contexte_sigalrm;

void gestionnaire_sigsigalrm()
{
  siglongjmp(contexte_sigalrm, 1);
}

int main(void)
{
  char ligne[80];
  int i;

  signal(SIGALRM, gestionnaire_sigsigalrm);
  fprintf(stdout, "Entrez un nombre entier avant 5s : ");
  if (sigsetjmp(contexte_sigalrm, 1) == 0)
  {
    alarm(5);

    while (1)
    {
      if (fgets(ligne, 79, stdin) != NULL)
        if (sscanf(ligne, "%d", &i) == 1)
          break;
    }

    alarm(0);
    fprintf(stdout, "ok !\n");
  }
  else
  {
    fprintf(stdout, "\n Trop tard !\n");
    exit(1);
  }
  return 0;
}