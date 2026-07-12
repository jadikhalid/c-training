#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

int main(void)
{
  int i;
  fprintf(stdout, "strsignal() :\n");
  for (i = 1; i < NSIG; i++)
    fprintf(stdout, "%d : %s\n", i, strsignal(i));

  return 0;
}