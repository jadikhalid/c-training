#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int main(void)
{
  pid_t pid;
  int status;
  switch (pid = fork())
  {
  case -1:
    fprintf(stderr, "Erreur dans fork()\n");
    exit(1);
  case 0:
    fprintf(stdout, "Fils 1 : PID = %u\n", getpid());
    while (1)
      pause();
  default:
    break;
  }
  switch (fork())
  {
  case -1:
    fprintf(stderr, "Erreur dans fork()\n");
    exit(1);
  }
}