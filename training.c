#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

void gestionnaire(int numero_signal)
{
  fprintf(stdout, "\n %u a recu le signal %d (%s)\n", getpid(), numero_signal, strsignal(numero_signal));
}

int main(void)
{
  for (int i = 1; i < _NSIG; i++)
    if (signal(i, gestionnaire) == SIG_ERR)
      fprintf(stderr, "Signal %d non capturé \n", i);
  while (1)
  {
    pause();
  }

  return 0;
}