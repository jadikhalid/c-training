#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gdbm.h>

static void construit_base(void);

int main(int argc, char *argv[])
{
    GDBM_FILE db;

    if (argc != 2)
    {
        fprintf(stderr, "La syntaxe doit obligatoirement etre de la forme : %s nom_base\n", argv[0]);
        exit(1);
    }

    /*
     * Ouverture de la base GDBM moderne.
     * Paramètres :
     * - argv[1] : le nom de la base
     * - 0 : taille de bloc par défaut (0 = optimal choisi par le système)
     * - GDBM_WRCREAT : ouvre en écriture et crée la base si elle n'existe pas
     * - 0644 : permissions du fichier (rw-r--r--)
     * - NULL : fonction de gestion des erreurs fatales par défaut
     */
    db = gdbm_open(argv[1], 0, GDBM_WRCREAT, 0644, NULL);

    if (db == NULL)
    {
        /* gdbm_strerror permet de récupérer un message d'erreur précis propre à GDBM */
        fprintf(stderr, "Erreur d'ouverture GDBM pour '%s' : %s\n", argv[1], gdbm_strerror(gdbm_errno));
        exit(1);
    }

    // ... Votre logique de manipulation de la base ici ...
    construit_base();

    // N'oubliez pas de fermer proprement la base à la fin !
    gdbm_close(db);

    return 0;
}

static void construit_base(void)
{
    FILE *fichier;
    char ligne[256];
    char *fin_ligne;
    size_t debut_ligne;
    int i = 0;
    char *nom = NULL;
    char *email = NULL;
    char *web = NULL;
    char *chaine;
    datum cle;
    datum donnee;
    int retour;

    if ((fichier = fopen("fichier_credits", "r")) == NULL)
    {
        perror("Erreure d'ouverture du fichier fichier_credits");
        return 1;
    }

    /* Sauter l'entete */
    while (1)
    {
        if (fgets(ligne, 256, fichier) == NULL)
            return 1;
        /* Supprimer commentaires et retours chariot */
        if ((fin_ligne = strpbrk(ligne, "\n\r#")) != NULL)
            fin_ligne[0] = '\0';
        if (strncmp(ligne, "--", 2) == 0)
            break;
    }
}
