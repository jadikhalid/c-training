#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysinfo.h>

int main(void)
{
    struct sysinfo info;

    if (sysinfo(&info) != 0)
    {
        perror("sysinfo error");
        exit(EXIT_FAILURE);
    }

    fprintf(stdout, "NB secondes depuis le boot : %ld\n", info.uptime);
    fprintf(stdout, "Charge systeme depuis une minute : %.2f%%\n", (double)info.loads[0] / 655.36);
    fprintf(stdout, "Charge systeme depuis 5 minutes : %.2f%%\n", (double)info.loads[1] / 655.36);
    fprintf(stdout, "Charge systeme depuis 10 minutes : %.2f%%\n", (double)info.loads[2] / 655.36);
    fprintf(stdout, "Mémoire disponible : %lu Mo\n", (unsigned long)(info.freeram >> 20));

    return 0;
}