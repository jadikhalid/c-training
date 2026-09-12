#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        fprintf(stderr, "Syntaxe : %s <chemin_jail> <commande> [args...]\n", argv[0]);
        exit(1);
    }

    // 1. Verrouiller la nouvelle racine (nécessite d'être root)
    if (chroot(argv[1]) != 0)
    {
        perror("chroot");
        exit(1);
    }

    // 2. Se placer à la racine de la nouvelle prison
    if (chdir("/") != 0)
    {
        perror("chdir");
        exit(1);
    }

    // 3. Abandonner les privilèges root (revenir à l'UID réel)
    if (seteuid(getuid()) < 0)
    {
        perror("seteuid");
        exit(1);
    }

    // 4. Remplacer l'image du processus par la commande ciblée
    execvp(argv[2], argv + 2);

    // Si execvp retourne, c'est qu'il y a eu une erreur
    perror("execvp");
    return 1;
}