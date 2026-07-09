#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/resource.h>

int main(void)
{
  pid_t pid;
  int status;
  struct rusage usage;

  switch (pid = fork())
  {
  case -1:
    fprintf(stderr, "Erreur dans fork()\n");
    exit(1);
  }
}
