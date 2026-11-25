#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    int tube[2];
    unsigned char buffer[256];
    int i;
    fprintf(stdout, "Création tube \n");
    if (pipe(tube) != 0)
    {
        perror("pipe");
        exit(1);
    }
    for (i = 0; i < 256; i++)
        buffer[i] = i;
    fprintf(stdout, "Ecriture dans tube \n");
}