#define _GNU_SOURCE

#include <search.h>
#include <stdio.h>
#include <string.h>

void ajoute_entree(char *nom, int numero, struct hsearch_data *table)
{
    ENTRY entree;
    ENTRY *retour;

    entree.key = strdup(nom);
    ;
    entree.data = (char *)numero;
    if (hsearch_r(entree, ENTER, &retour, table) == 0)
    {
        perror("hsearch_r");
        exit(1);
    }
}

int main(int argc, char *argv[])
{
    struct hsearch_data table;
    int i;
    ENTRY entree;
    ENTRY *trouve;

    if (argc < 2)
    {
        fprintf(stderr, "Syntaxe : %s nom-departement \n", argv[0]);
        exit(1);
    }

    memset(&table, 0, sizeof(table));
}