#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    sigset_t ensemble;
    int numero;
    struct timespec delai;

    fprintf(stdout, "PID=%u\n", getpid());

    /* Blocage de tous les signaux */
    sigfillset(&ensemble);
    sigprocmask(SIG_BLOCK, &ensemble, NULL);

    /* Attente de tous les signaux pendant 10 secondes */
    delai.tv_sec = 10;
    delai.tv_nsec = 0;

    sigfillset(&ensemble);
    while (1)
    {
        if ((numero = sigtimedwait(&ensemble, NULL, &delai)) < 0)
        {
            perror("Erreur a l'appel de sigtimedwait");
            break;
        }
        fprintf(stdout, "sigtimedwait %d reçu \n", numero);
    }

    return 0;
}