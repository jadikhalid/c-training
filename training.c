#define _GNU_SOURCE

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NB_THREADS 5

void *fn_thread(void *numero);

static int compteur = 0;

int main(void)
{
  pthread_t thread[NB_THREADS];
  int i;
  int ret;

  for (i = 0; i < NB_THREADS; i++)
    if ((ret = pthread_create(&thread[i], NULL, fn_thread, (void *)i)) != 0)
    {
      fprintf(stderr, "%s", strerror(ret));
      exit(1);
    }
}