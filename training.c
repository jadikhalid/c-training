#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int tube[2];
    pid_t pid;

    if (argc != 3)
    {
        fprintf(stderr, "Syntaxe : %s commande_1 commande_2\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (pipe(tube) != 0)
    {
        perror("pipe");
        return EXIT_FAILURE;
    }

    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        close(tube[0]);
        close(tube[1]);
        return EXIT_FAILURE;
    }

    if (pid == 0)
    {
        /* Fils : execute commande_1 et ecrit sa sortie standard dans le tube */
        close(tube[0]);
        if (dup2(tube[1], STDOUT_FILENO) < 0)
        {
            perror("dup2");
            close(tube[1]);
            _exit(EXIT_FAILURE);
        }
        close(tube[1]);

        if (system(argv[1]) == -1)
        {
            perror("system");
            _exit(EXIT_FAILURE);
        }
        _exit(EXIT_SUCCESS);
    }

    /* Pere : lit l'entree standard depuis le tube et execute commande_2 */
    close(tube[1]);
    if (dup2(tube[0], STDIN_FILENO) < 0)
    {
        perror("dup2");
        close(tube[0]);
        wait(NULL);
        return EXIT_FAILURE;
    }
    close(tube[0]);

    if (system(argv[2]) == -1)
    {
        perror("system");
        wait(NULL);
        return EXIT_FAILURE;
    }

    if (wait(NULL) < 0)
    {
        perror("wait");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}