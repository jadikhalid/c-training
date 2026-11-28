#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

static void retirer_newline(char *s)
{
    size_t len = strlen(s);
    if (len > 0 && s[len - 1] == '\n')
        s[len - 1] = '\0';
}

int main(void)
{
    FILE *question;
    FILE *reponse;
    int fd;
    char nom_fifo[128];
    char chaine[128];

    fprintf(stdout, "Chaine a traiter : ");
    fflush(stdout);
    if (fgets(chaine, sizeof(chaine), stdin) == NULL)
        return 0;
    retirer_newline(chaine);

    snprintf(nom_fifo, sizeof(nom_fifo), "anagramme.%u", (unsigned)getpid());
    unlink(nom_fifo);
    if (mkfifo(nom_fifo, 0644) != 0)
    {
        perror("mkfifo client");
        return 1;
    }

    fd = open("anagramme.fifo", O_WRONLY);
    if (fd < 0)
    {
        perror("open anagramme.fifo");
        unlink(nom_fifo);
        return 1;
    }

    question = fdopen(fd, "w");
    if (question == NULL)
    {
        perror("fdopen question");
        close(fd);
        unlink(nom_fifo);
        return 1;
    }

    fprintf(question, "%s\n%s\n", nom_fifo, chaine);
    fclose(question); /* ferme aussi fd et envoie les octets au serveur */

    /* Débloque dès que le serveur ouvre nom_fifo en écriture */
    fd = open(nom_fifo, O_RDONLY);
    if (fd < 0)
    {
        perror("open fifo reponse");
        unlink(nom_fifo);
        return 1;
    }

    reponse = fdopen(fd, "r");
    if (reponse != NULL)
    {
        if (fgets(chaine, sizeof(chaine), reponse) != NULL)
        {
            retirer_newline(chaine);
            fprintf(stdout, "Reponse = %s\n", chaine);
        }
        else
        {
            perror("fgets reponse");
        }
        fclose(reponse);
    }
    else
    {
        perror("fdopen reponse");
        close(fd);
    }

    unlink(nom_fifo);
    return 0;
}