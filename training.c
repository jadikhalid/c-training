#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <errno.h>

void *fn_thread(void *inutile00)
{
  (void)inutile00;
  char chaine[128];
  int i = 0;
  fprintf(stdout, "Thread : entrez un nombre :");
  while (fgets(chaine, 128, stdin) != NULL)
    if (sscanf(chaine, "%d", &i) != 1)
      fprintf(stdout, "Un nombre SVP :");
    else
      break;
  pthread_exit((void *)(intptr_t)i);
}

int main(void)
{
  int i;
  int ret;
  void *retour;
  pthread_t thread;

  if ((ret = pthread_create(&thread, NULL, fn_thread, NULL)) != 0)
  {
    perror("Erreur lors de la creation du thread");
    exit(1);
  }

  pthread_join(thread, &retour);

  if (retour != PTHREAD_CANCELED)
  {
    i = (int)(intptr_t)retour;
    fprintf(stdout, "main : valeur lue = %d\n", i);
  }

  return 0;
}