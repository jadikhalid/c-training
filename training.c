#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main(void)
{
    int fd;
    unsigned int masque;
    masque = umask(0);
    fprintf(stdout, "Ancien masque = %o, nouveau = 0 \n", masque);
    fprintf(stdout, "Tentatie de creation de essai.umask \n");
    fd = open("essai.umask", O_RDWR | O_CREAT | O_EXCL, 0777);
    if (fd < 0)
    {
        perror("open");
        exit(1);
    }
    else
        close(fd);
    system("ls -l essai.umask");
    unlink("essai.umask");

    umask(masque);

    fprintf(stdout, "Remise masque = %o \n", masque);
    fprintf(stdout, "Tentative de creation de essai.umask");

    fd = open("essai.umask", O_RDWR | O_CREAT | O_EXCL, 0777);
    if (fd < 0)
    {
        perror("open");
        exit(1);
    }
    else
        close(fd);
    system("ls -l essai.umask");
    unlink("essai.umask");

    return 0;
}