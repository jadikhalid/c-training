#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void lecture_contenu(const char *nom)
{
    char *buffer = NULL;
    char *nouveau = NULL;
    size_t taille = 0;
    ssize_t nb_copies;

    while (1)
    {
        taille += 16;
        nouveau = realloc(buffer, taille);
        if (nouveau == NULL)
        {
            perror("realloc");
            break;
        }
        buffer = nouveau;

        nb_copies = readlink(nom, buffer, taille - 1);
        if (nb_copies == -1)
        {
            perror(nom);
            break;
        }

        // Si le nombre d'octets lus est strictement inférieur à la capacité du buffer,
        // cela signifie que tout le chemin cible du lien a été lu.
        if ((size_t)nb_copies < taille - 1)
        {
            buffer[nb_copies] = '\0';
            printf("%s -> %s\n", nom, buffer);
            break;
        }
    }

    free(buffer);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <lien_symbolique1> [lien_symbolique2 ...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc; i++)
    {
        lecture_contenu(argv[i]);
    }

    return EXIT_SUCCESS;
}