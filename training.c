#define _GNU_SOURCE

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <rpc/des_crypt.h>

int main(int argc, char *argv[])
{
    char *nom_programme;
    int fichier;
    struct stat etat_fichier;
    char *projection;
    char cle[8];
    unsigned int mode;
    int retour;

    if (argc != 3)
    {
        fprintf(stderr, "Syntaxe : %s : fichier clé\n", argv[0]);
        exit(1);
    }
    nom_programme = basename(argv[0]);
}
