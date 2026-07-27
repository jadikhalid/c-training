#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void affiche_status(pid_t pid)
{
  FIle *fp;
  char chaine[80];
  sprintf(chaine, "/proc/%u/status", pid);
}