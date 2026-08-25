#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    double x;
    double y;
    double z;
} point_t;

int main(void)
{
    point_t *table;
    size_t n = 8; // Correction 1 : Initialisation explicite à 8
    size_t i;     // Utilisation de size_t pour correspondre à n
    FILE *fp;

    table = (point_t *)calloc(n, sizeof(point_t));
    if (table == NULL)
    {
        perror("calloc");
        exit(1);
    }

    /* Initialisation */
    table[0].x = -1.0;
    table[0].y = -1.0;
    table[0].z = -1.0;
    table[1].x = 1.0;
    table[1].y = -1.0;
    table[1].z = -1.0; // Corrigé x=1.0 pour un vrai cube
    table[2].x = -1.0;
    table[2].y = 1.0;
    table[2].z = -1.0;
    table[3].x = 1.0;
    table[3].y = 1.0;
    table[3].z = -1.0;
    table[4].x = -1.0;
    table[4].y = -1.0;
    table[4].z = 1.0;
    table[5].x = 1.0;
    table[5].y = -1.0;
    table[5].z = 1.0;
    table[6].x = -1.0;
    table[6].y = 1.0;
    table[6].z = 1.0;
    table[7].x = 1.0;
    table[7].y = 1.0;
    table[7].z = 1.0;

    /* Sauvegarde */
    if ((fp = fopen("essai.fread", "wb")) == NULL) // "wb" pour écriture binaire
    {
        perror("fopen");
        exit(1);
    }

    /* Écriture du nombre de points (n), suivi de la table */
    // Correction 2 : On écrit sizeof(size_t) pour correspondre au type de n
    if ((fwrite(&n, sizeof(size_t), 1, fp) != 1) || (fwrite(table, sizeof(point_t), n, fp) != n))
    {
        perror("fwrite");
        fclose(fp);
        exit(1);
    }

    fclose(fp);

    free(table);
    table = NULL;
    n = 0;

    /* Récupération */
    if ((fp = fopen("essai.fread", "rb")) == NULL) // "rb" pour lecture binaire
    {
        perror("fopen");
        exit(1);
    }

    // Lecture de la taille stockée
    if (fread(&n, sizeof(size_t), 1, fp) != 1)
    {
        perror("fread size");
        fclose(fp);
        exit(1);
    }

    // Allocation de la taille exacte lue
    if ((table = (point_t *)calloc(n, sizeof(point_t))) == NULL)
    {
        perror("calloc");
        fclose(fp);
        exit(1);
    }

    // Correction 3 : Vérification du retour par rapport à n et non la valeur en dur 8
    if (fread(table, sizeof(point_t), n, fp) != n)
    {
        perror("fread table");
        fclose(fp);
        exit(1);
    }

    fclose(fp);

    /* Affichage */
    for (i = 0; i < n; i++)
    {
        fprintf(stdout, "point[%zu] : % f, % f, % f \n", i, table[i].x, table[i].y, table[i].z);
    }

    /* Nettoyage final */
    free(table);
    table = NULL;

    return 0;
}