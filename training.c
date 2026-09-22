#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wordexp.h>
#include <sys/wait.h>

void affiche_erreur(int numero)
{
    switch ((numero))
    {
    case WRDE_BADCHAR:
        fprintf(stderr, "Caractere interdit \n");
        break;
    case WRDE_BADVAL:
        fprintf(stderr, "Variable indéfinie \n");
        break;
    case WRDE_CMDSUB:
        fprintf(stderr, "Invocation de commande interdite \n");
        break;
    case WRDE_NOSPACE:
        fprintf(stderr, "Pas assez de mémoire \n");
        break;
    case WRDE_SYNTAX:
        fprintf(stderr, "Erreur de syntaxe \n");
        break;
    default:
        break;
    }
}

#define LG_LINE 256

int main(void)
{
    char ligne[LG_LINE];
    wordexp_t mots;
    int erreur;
    pid_t pid;
    while (1)
    {
        /* Lecture de la commande */
        fprintf(stdout, "-> ");
        if (fgets(ligne, LG_LINE, stdin) == NULL)
            break;
    }
}