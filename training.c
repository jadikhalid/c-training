#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gdbm.h>

void affiche_contibuteur(datum cle, datum donnee);

int main(int argc, char *argv[])
{
    datum cle;
    datum donnee;
    char chaine[256];
    char *fin_chaine;
    GDBM_FILE db;

    if (argc != 2)
    {
        fprintf(stderr, "Synatxe : %s nom_base\n", argv[0]);
        exit(1);
    }
    db = gdbm_open(argv[1], 0, GDBM_WRCREAT, 0644, NULL);
    if (db == NULL)
    {
        perror("db");

        exit(1);
    }
    while (1)
    {
        fprintf(stdout, "(Nom)> ");
        if (fgets(chaine, 256, stdin) == NULL)
            break;
        if ((fin_chaine = strpbrk(chaine, "\n\r ")) != NULL)
            *fin_chaine = '\0';
        if (strlen(chaine) == 0)
            continue;
        for (cle = gdbm_firstkey(db); cle.dptr != NULL; cle = gdbm_nextkey(db, cle))
        {
            donnee = gdbm_fetch(db, cle);
            if (donnee.dptr != NULL)
                if (strstr(donnee.dptr, chaine) != NULL)
                    affiche_contibuteur(cle, donnee);
        }
    }
    fprintf(stdout, "\n");
    gdbm_close(db);
    return 0;
}

void affiche_contibuteur(datum cle, datum donnee)
{
    char *nom;
    char *email;
    char *web;

    nom = donnee.dptr;
    email = &(nom[strlen(nom) + 1]);
    web = &(email[strlen(email) + 1]);
    fprintf(stdout, "Numero : %d\n", *((int *)cle.dptr));
    fprintf(stdout, "Nom : %s\n", nom);
    fprintf(stdout, "Email : %s\n", email);
    fprintf(stdout, " Web : %s\n", web);
}