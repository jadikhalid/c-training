#define _GNU_SOURCE
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

static const char *nom_noeud = "anagramme.fifo";

static void retirer_newline(char *s)
{
    size_t len = strlen(s);
    if (len > 0 && s[len - 1] == '\n')
        s[len - 1] = '\0';
}

static int repondre(const char *nom_fifo, char *chaine)
{
    int fd;
    FILE *reponse;
    char *anagramme;

    if (nom_fifo[0] == '\0')
        return 0;

    fd = open(nom_fifo, O_WRONLY);
    if (fd >= 0)
    {
        reponse = fdopen(fd, "w");
        if (reponse != NULL)
        {
            anagramme = strdup(chaine);
            if (anagramme != NULL)
            {
                strfry(anagramme);
                fprintf(reponse, "%s\n", anagramme);
                free(anagramme);
            }
            fclose(reponse); /* ferme aussi fd */
        }
        else
        {
            close(fd);
        }
    }
    else
    {
        perror("open reponse");
    }

    if (strcasecmp(chaine, "FIN") == 0 || strcasecmp(nom_fifo, "FIN") == 0)
        return 1;

    return 0;
}

int main(void)
{
    FILE *fichier;
    int fd;
    char nom_fifo[128];
    char chaine[128];

    unlink(nom_noeud); /* nettoie un éventuel résidu d'exécution précédente */
    if (mkfifo(nom_noeud, 0644) != 0)
    {
        perror("mkfifo");
        return 1;
    }

    fd = open(nom_noeud, O_RDWR);
    if (fd < 0)
    {
        perror("open fifo serveur");
        unlink(nom_noeud);
        return 1;
    }

    fichier = fdopen(fd, "r");
    if (fichier == NULL)
    {
        perror("fdopen");
        close(fd);
        unlink(nom_noeud);
        return 1;
    }

    while (1)
    {
        if (fgets(nom_fifo, sizeof(nom_fifo), fichier) == NULL)
            break;
        retirer_newline(nom_fifo);

        if (fgets(chaine, sizeof(chaine), fichier) == NULL)
            break;
        retirer_newline(chaine);

        if (repondre(nom_fifo, chaine) != 0)
            break;
    }

    fclose(fichier); /* ferme aussi fd */
    unlink(nom_noeud);
    return 0;
}