#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

FILE *fopen_exclusif(const char *nom_fichier, const char *mode_flux)
{
    int lecture = 0;
    int ecriture = 0;
    int ajout = 0;
    int creation = 0;
    int troncature = 0;
    int flags = 0;
    size_t i;
    int fd;
    FILE *fp;

    for (i = 0; i < strlen(mode_flux); i++)
    {
        switch (mode_flux[i])
        {
        case 'a':
            ecriture = creation = ajout = 1;
            break;
        case 'r':
            lecture = 1;
            break;
        case 'w':
            ecriture = creation = troncature = 1;
            break;
        case '+':
            ecriture = lecture = 1;
            break;
        default:
            break;
        }
    }

    if (lecture && ecriture)
        flags = O_RDWR;
    else if (lecture)
        flags = O_RDONLY;
    else if (ecriture)
        flags = O_WRONLY;
    else
    {
        errno = EINVAL;
        return NULL;
    }

    // O_EXCL n'est activé QUE si le mode demande la création d'un fichier ('w' ou 'a')
    if (creation)
        flags |= O_CREAT | O_EXCL;

    if (troncature)
        flags |= O_TRUNC;

    if (ajout)
        flags |= O_APPEND;

    fd = open(nom_fichier, flags, 0644);

    if (fd < 0)
        return NULL; // open a déjà configuré errno (ex: EEXIST si le fichier existe déjà)

    fp = fdopen(fd, mode_flux);
    if (fp == NULL)
    {
        close(fd);
        return NULL;
    }

    return fp;
}

void ouverture(const char *nom, const char *mode, int execlusif)
{
    FILE *fp;
    fprintf(stderr, "Ouverture %s de %s, mode %s :", (execlusif ? "exclusif" : ""), nom, mode);
    if (execlusif)
        fp = fopen_exclusif(nom, mode);
    else
        fp = fopen(nom, mode);

    if (fp == NULL)
    {
        fprintf(stderr, " ");
        perror("ÉCHEC");
    }
    else
    {
        fprintf(stderr, "OK\n");
        fclose(fp);
    }
}

int main(void)
{
    ouverture("essai.open_3", "w+", 1);
    ouverture("essai.open_3", "w+", 1);
    ouverture("essai.open_3", "w+", 0);

    return 0;
}