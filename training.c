#include <locale.h>
#include <monetary.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    double d = 0.0;
    char buffer[80];

    if (setlocale(LC_ALL, "") == NULL)
    {
        fprintf(stderr, "Avertissement : impossible d'appliquer la locale environnementale.\n");
    }

    if ((argc != 3) || (sscanf(argv[2], "%lf", &d) != 1))
    {
        fprintf(stderr, "Usage : %s <format> <valeur>\n", argv[0]);
        return EXIT_FAILURE;
    }

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-nonliteral"
    if (strfmon(buffer, sizeof(buffer), argv[1], d) < 0)
    {
#pragma GCC diagnostic pop
        perror("strfmon");
        return EXIT_FAILURE;
    }

    fprintf(stdout, "%s\n", buffer);
    return EXIT_SUCCESS;
}