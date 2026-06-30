#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
  int i;
  pid_t pid, sid;
  if (argc == 1)
  {
    fprintf(stdout, "%d : %d\n", getpid(), getsid(0));
    return 0;
  }
  for (i = 1; i < argc; i++)
    if (sscanf(argv[i], "%d", &pid) != 1)
      fprintf(stderr, "PID invalide : %s\n", argv[i]);
    else
    {
      sid = getsid(pid);
      if (sid == -1)
        fprintf(stderr, "%d inexistant\n", pid);
      else
        fprintf(stdout, "%d : %d\n", pid, sid);
    }

  return 0;
}