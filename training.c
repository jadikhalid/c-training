#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 80

typedef enum
{
  VALIDATION_OK,
  ERR_SISS_VIDE,
  ERR_ESPACE_INTERNE,
  ERR_CHAR_INTERDIT
} CodeValidation;

CodeValidation valider_et_nettoyer_nom(char *chaine_brute, char **chaine_propre)
{
  // 1- Supprimer le saut de ligne \n de fgets
  size_t len = strlen(chaine_brute);
  if (len > 0 && chaine_brute[len - 1] == '\n')
  {
    chaine_brute[len - 1] = '\0';
  }
  // 2- Nettoyage des espaces aux extremites (Trim)
  char *debut = chaine_brute;
  while (isspace((unsigned char)*debut))
    debut++;
  if (*debut == '\0')
  {
    return ERR_SISS_VIDE;
  }
  char *fin = debut + strlen(debut) - 1;
  while (fin > debut && isspace((unsigned char)*fin))
    fin--;
  fin[1] = '\0';

  // On passe le pointeur nettoyé au programme principal
  *chaine_propre = debut;

  // 3. Vérification des espaces internes (ex: "fi chier.txt")
  char *p = debut;
  while (*p)
  {
    if (isspace((unsigned char)*p))
    {
      return ERR_ESPACE_INTERNE;
    }
    p++;
  }

  // 4. Vérification des caractères interdits OS (\ / : * ? " < > |)
  const char *interdits = "\\/:*?\"<>|";
  if (strpbrk(debut, interdits) != NULL)
  {
    return ERR_CHAR_INTERDIT;
  }

  return VALIDATION_OK; // La saisie a passé tous les contrôles
}

int main()
{
  char raw_buffer[BUFFER_SIZE];
  char *nom_fichier_nettoye = NULL;
  FILE *fp = NULL;
  int saisie_valide = 0;

  while (!saisie_valide)
  {
    printf("Entrez le nom du fichier : ");
    fflush(stdout);

    if (fgets(raw_buffer, sizeof(raw_buffer), stdin) == NULL)
    {
      fprintf(stderr, "\nFin de flux détectée. Quitter.\n");
      return EXIT_FAILURE;
    }

    // Gestion du débordement technique de STDIN
    size_t len = strlen(raw_buffer);
    if (len == BUFFER_SIZE - 1 && raw_buffer[len - 1] != '\n')
    {
      fprintf(stderr, "Erreur : Saisie trop longue.\n\n");
      int c;
      while ((c = getchar()) != '\n' && c != EOF)
        ;
      continue;
    }

    // Appel du bloc de validation unique
    CodeValidation resultat = valider_et_nettoyer_nom(raw_buffer, &nom_fichier_nettoye);

    // Traitement du diagnostic
    switch (resultat)
    {
    case ERR_SISS_VIDE:
      fprintf(stderr, "Erreur : Le nom ne peut pas être vide.\n\n");
      continue;
    case ERR_ESPACE_INTERNE:
      fprintf(stderr, "Erreur : Les espaces internes sont interdits (plusieurs mots détectés).\n\n");
      continue;
    case ERR_CHAR_INTERDIT:
      fprintf(stderr, "Erreur : Caractères système interdits détectés (\\ / : * ? \" < > |).\n\n");
      continue;
    case VALIDATION_OK:
      // Tout est validé par la fonction, on peut tenter l'ouverture
      fp = fopen(nom_fichier_nettoye, "rb");
      if (fp == NULL)
      {
        fprintf(stderr, "Erreur : Impossible d'ouvrir '%s' (Fichier introuvable/protégé).\n\n", nom_fichier_nettoye);
      }
      else
      {
        saisie_valide = 1; // Le fichier existe et est ouvert !
      }
      break;
    }
  }

  printf("\nSuccès ! Le fichier '%s' est prêt pour le traitement.\n", nom_fichier_nettoye);
  // --- DÉBUT DU BLOC DE LECTURE (À insérer après la validation) ---
  printf("\n--- Analyse du fichier (Blocs de 128 octets) ---\n\n");

  unsigned char bloc[128];
  size_t bytes_read;
  unsigned int compteur_bloc = 1;

  // Étape 1 : Boucle de lecture par bloc
  while ((bytes_read = fread(bloc, 1, sizeof(bloc), fp)) > 0)
  {
    printf("Bloc %03u [%zu octets] : \n", compteur_bloc++, bytes_read);

    // Étape 2 : Affichage de la partie Hexadécimale
    for (size_t i = 0; i < bytes_read; i++)
    {
      printf("%02X ", bloc[i]);

      // Optionnel : un espace supplémentaire tous les 16 octets pour aérer
      if ((i + 1) % 16 == 0)
        printf(" ");
    }

    // Étape 3 : Alignement (Padding) si le dernier bloc fait moins de 128 octets
    // Chaque octet manquant en hexa occupait 3 caractères (2 lettres + 1 espace)
    size_t octets_manquants = sizeof(bloc) - bytes_read;
    for (size_t i = 0; i < octets_manquants; i++)
    {
      printf("   ");
    }
    // Compensation de l'aération optionnelle des blocs de 16
    printf("   ");

    // Séparateur entre l'Hexa et l'ASCII
    printf(" | ");

    // Étape 4 : Affichage de la partie ASCII
    for (size_t i = 0; i < bytes_read; i++)
    {
      // On vérifie si le caractère est imprimable à l'écran
      if (isprint(bloc[i]))
      {
        printf("%c", bloc[i]);
      }
      else
      {
        printf("."); // Remplacement des caractères invisibles
      }
    }

    printf("\n\n"); // Fin du bloc actuel
  }
  // --- FIN DU BLOC DE LECTURE ---
  fclose(fp);
  return EXIT_SUCCESS;
}
