#include <stdio.h>
#include <string.h>

#define LG_MAXI 32

int main(int argc, char *argv[])
{
    int i;
    unsigned long int taille;
    char chaine[LG_MAXI + 1];
    strcpy(chaine, "Arguments : ");
    for (i = 1; i < argc; i++)
    {
        taille = strlen(chaine);
        strncat(chaine, argv[i], LG_MAXI - taille);
    }
    fprintf(stdout, "%s\n", chaine);

    return 0;
}