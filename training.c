#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <time.h>

// Déclaration indispensable de la variable globale d'erreur de getdate()
extern int getdate_err;

int main(int argc, char *argv[])
{
    struct tm *tm;
    int i;

    // Vérification de base pour rappeler l'utilisation de DATEMSK
    // (ex: export DATEMSK="/chemin/vers/fichier_de_motifs")
    for (i = 1; i < argc; i++)
    {
        fprintf(stdout, "%s : ", argv[i]);

        tm = getdate(argv[i]);

        if (tm == NULL)
        {
            switch (getdate_err)
            {
            case 1:
                fprintf(stdout, "DATEMSK indéfinie\n");
                break;
            case 2:
                fprintf(stdout, "Motifs non ouverts\n");
                break;
            case 3:
                fprintf(stdout, "Motifs inaccessibles\n");
                break;
            case 4:
                fprintf(stdout, "Motifs non réguliers\n");
                break;
            case 5:
                fprintf(stdout, "Motifs non lus\n");
                break;
            case 6:
                fprintf(stdout, "Mémoire insuffisante\n");
                break;
            case 7:
                fprintf(stdout, "Motifs introuvables\n");
                break;
            case 8:
                fprintf(stdout, "Chaîne invalide\n");
                break;
            default:
                fprintf(stdout, "Erreur inconnue (code %d)\n", getdate_err);
                break;
            }
        }
        else
        {
            fprintf(stdout, "%s", asctime(tm));
        }
    }

    return 0;
}