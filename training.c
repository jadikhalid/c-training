#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main(int argc, char *argv[])
{
    char *projection;
    int fichier;
    struct stat etat_fichier;
    long taille_fichier;
    int i;
    char tmp;

    if (argc != 2)
    {
        fprintf(stderr, "Syntaxe : %s fichier á inverser\n", argv[0]);
        ext(1);
    }
    if ((fichier = open(arg[1], O_RDWR)) < 0)
    {
        perror("Erreure á l'ouverture du fichier");
        exit(1);
    }
}