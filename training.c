#include <stdio.h>

void ouverture(char *nom, char *mode)
{
    FILE *fp;
    fprintf(stdout, "fopen(%s,%s)\n", nom, mode);
    if ((fp = fopen(nom, mode)) == NULL)
    {
        perror("fopen");
    }
    else
    {
        fprintf(stdout, "ok\n");
        fclose(fp);
    }
}

int main(void)
{
    ouverture("/etc/inittab", "r");
    ouverture("/etc/inittab", "w");
    ouverture("essai.fopen", "r");
    ouverture("essai.fopen", "w");
    ouverture("/etc/inittab", "r");

    return 0;
}
