#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gdbm.h>

void affiche_contibuteur(datum cle, datum donnee);

int main(int argc, char *argv[])
{
    GDBM_FILE base;
    datum cle;
    datum donnee;

    if (argc != 2)
    {
        fprintf(stderr, "Syntaxe : %s nom_de_la_base \n", argv[0]);
        exit(1);
    }

    if ((base = gdbm_open(argv[1], 0, GDBM_READER, 0, NULL)) == NULL)
    {
        fprintf(stderr, "%s : %s\n", argv[1], gdbm_strerror(gdbm_errno));
        exit(1);
    }

    for (cle = gdbm_firstkey(base); cle.dptr != NULL;)
    {
        donnee = gdbm_fetch(base, cle);
        if (donnee.dptr != NULL)
        {
            affiche_contibuteur(cle, donnee);
            free(donnee.dptr); // Libération de la donnée
        }

        // Récupération de la clé suivante avant de libérer la courante
        datum prochaine_cle = gdbm_nextkey(base, cle);
        free(cle.dptr); // Libération de l'ancienne clé
        cle = prochaine_cle;
    }

    gdbm_close(base);
    return 0;
}

void affiche_contibuteur(datum cle, datum donnee)
{
    // Sécurité de la clé avec cast explicite pour -Wsign-compare
    if (cle.dptr != NULL && cle.dsize > 0 && (size_t)cle.dsize >= sizeof(int))
    {
        fprintf(stdout, "Numero : %d\n", *((int *)cle.dptr));
    }
    else
    {
        fprintf(stdout, "Numero : (invalide)\n");
    }

    // Vérification de la taille de la donnée pour -Wsign-conversion
    if (donnee.dsize < 0)
    {
        fprintf(stderr, "Donnée corrompue (taille négative)\n");
        return;
    }

    char *ptr = donnee.dptr;
    size_t taille_restante = (size_t)donnee.dsize;

    // Extraction sécurisée du Nom
    size_t len_nom = strnlen(ptr, taille_restante);
    if (len_nom >= taille_restante)
    {
        fprintf(stderr, "Donnée corrompue (Nom)\n");
        return;
    }
    char *nom = ptr;
    ptr += len_nom + 1;
    taille_restante -= len_nom + 1;

    // Extraction sécurisée de l'Email
    size_t len_email = strnlen(ptr, taille_restante);
    if (len_email >= taille_restante)
    {
        fprintf(stderr, "Donnée corrompue (Email)\n");
        return;
    }
    char *email = ptr;
    ptr += len_email + 1;
    taille_restante -= len_email + 1;

    // Extraction sécurisée du Web
    size_t len_web = strnlen(ptr, taille_restante);
    if (len_web > taille_restante)
    {
        fprintf(stderr, "Donnée corrompue (Web)\n");
        return;
    }
    char *web = ptr;

    fprintf(stdout, "Nom : %s\n", nom);
    fprintf(stdout, "Email : %s\n", email);
    fprintf(stdout, "Web : %s\n", web);
    fprintf(stdout, "---------------------------\n");
}