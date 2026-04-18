/*
 * Programme : coder_pro.c
 * Syntaxe : ./coder_pro [fichier] [action: C ou D] [cle]
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// On passe le caractère, la clé complète, et la position actuelle
int encode_character(int ch, const char *key, int pos);
int decode_character(int ch, const char *key, int pos);

int main(int argc, char *argv[])
{
  FILE *fh;
  int ch = 0;
  int pos = 0;
  char buffer[257];

  if (argc != 4)
  {
    printf("\nErreur: Parametres manquants.");
    printf("\nSyntaxe: %s [fichier] [action: C/D] [cle]\n", argv[0]);
    return EXIT_FAILURE;
  }

  char *key = argv[3];
  char action = argv[2][0];

  // MODE DECODAGE (Lecture du fichier existant)
  if (action == 'D' || action == 'd')
  {
    fh = fopen(argv[1], "r");
    if (fh == NULL)
    {
      perror("\nErreur d'ouverture");
      return EXIT_FAILURE;
    }

    printf("--- Contenu Décodé ---\n");
    while ((ch = fgetc(fh)) != EOF)
    {
      // On ne décode pas le retour à la ligne pour garder la structure
      if (ch == '\n')
      {
        putchar('\n');
        pos = 0; // Reset de la position de la clé par ligne
      }
      else
      {
        putchar(decode_character(ch, key, pos));
        pos++;
      }
    }
    fclose(fh);
    printf("\n----------------------\n");
  }
  // MODE CODAGE (Création du fichier)
  else if (action == 'C' || action == 'c')
  {
    fh = fopen(argv[1], "w");
    if (fh == NULL)
    {
      perror("\nErreur de création");
      return EXIT_FAILURE;
    }

    printf("Entrez le texte a coder (Entree pour valider, Ligne vide pour finir) :\n");
    while (fgets(buffer, sizeof(buffer), stdin))
    {
      if (buffer[0] == '\n')
        break;

      for (size_t i = 0; i < strlen(buffer); i++)
      {
        if (buffer[i] == '\n')
        {
          fputc('\n', fh);
          pos = 0;
        }
        else
        {
          ch = encode_character(buffer[i], key, pos);
          fputc(ch, fh);
          pos++;
        }
      }
    }
    fclose(fh);
    printf("\nMessage codé avec la clé '%s' et enregistré dans %s.\n", key, argv[1]);
  }

  return EXIT_SUCCESS;
}

// Utilise la valeur ASCII du caractère de la clé pour le décalage + XOR
int encode_character(int ch, const char *key, int pos)
{
  int k = key[pos % strlen(key)]; // On boucle sur la clé
  return (ch + k) ^ k;            // Mélange complexe
}

int decode_character(int ch, const char *key, int pos)
{
  int k = key[pos % strlen(key)];
  return (ch ^ k) - k; // Inversion exacte
}