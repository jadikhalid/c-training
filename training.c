#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Portablité windows / posix
#if (defined(_WIN32) || defined(_WIN64)) && !defined(__MINGW32__) && !defined(__MSYS__)
#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>

static inline int mkstemp(char *template_name)
{
  if (_mktemp_s(template_name, strlen(template_name) + 1) != 0)
  {
    return -1;
  }
  return _open(template_name, _O_CREAT | _O_RDWR | _O_BINARY, _S_IREAD | _S_IWRITE);
}

#define close _close
#else
#include <unistd.h>
#endif

// Variables globales pour le mécanisme d'atexit()
FILE *fp_temporaire = NULL;
char nom_fichier_temp[256] = {0};

// 1. Fonction de nettoyage enregitré par atexit()
void nettoyer_fichier_temporaire(void)
{
  if (fp_temporaire != NULL)
  {
    fclose(fp_temporaire);
    printf("\n[Nettoyage] Fichier temporaire ferme automatiquement.\n");
  }
  if (nom_fichier_temp[0] != '\0')
  {
    remove(nom_fichier_temp);
    printf("[Nettoyage] Fichier temporaire supprime physiquement du disque.\n");
  }
}

// 2. La fonction demandée : Ouvre un fichier temporaire dans un mode spécifié
FILE *ouvrir_fichier_temporaire(const char *mode)
{
  // On prépare le modèle de nom (les XXXXXX seront remplacés par l'alias mkstemp)
  strcpy(nom_fichier_temp, "temp_jadi_XXXXXX");

  // Utilisation de mkstemp (soit la version native POSIX, soit notre alias Windows)
  int fd = mkstemp(nom_fichier_temp);

  if (fd == -1)
  {
    return NULL; // Échec de la génération ou de la création
  }

// Associe le descripteur de fichier brut à un flux FILE* avec le mode choisi
#if defined(_WIN32) || defined(_WIN64)
  fp_temporaire = _fdopen(fd, mode);
#else
  fp_temporaire = fdopen(fd, mode);
#endif

  if (fp_temporaire == NULL)
  {
    close(fd); // Sécurité : ferme le descripteur brut si l'association échoue
    return NULL;
  }

  // Enregistrement de la fonction de nettoyage
  static int atexit_enregistre = 0;
  if (!atexit_enregistre)
  {
    atexit(nettoyer_fichier_temporaire);
    atexit_enregistre = 1;
  }

  return fp_temporaire;
}

int main()
{
  // On ouvre le fichier dans le mode spécifié (ex: "w+" pour lecture/écriture)
  FILE *fp = ouvrir_fichier_temporaire("w+");

  char tableau[] = "bonjour, je m'appelle Jadi Khalidé\nJe suis entrain d'écrire un progamme.";
  char tableaufinal[80];
  size_t taille_lue;

  if (fp == NULL)
  {
    fprintf(stderr, "Erreur lors de la creation du fichier temporaire\n");
    return 1;
  }

  // Écriture du texte
  fprintf(fp, "%s", tableau);
  rewind(fp);

  // Lecture de la première ligne
  if (fgets(tableaufinal, sizeof(tableaufinal), fp) != NULL)
  {
    printf("La premiere ligne est : %s", tableaufinal);
    taille_lue = strlen(tableaufinal);
    printf("Octets lus: %zu | Taille memoire tableau: %zu\n\n", taille_lue, sizeof(tableau));
  }
  else
  {
    fprintf(stderr, "Erreur lors de la lecture de la premiere ligne\n");
    return 1;
  }

  // Lecture de la deuxième ligne
  if (fgets(tableaufinal + taille_lue, sizeof(tableaufinal) - taille_lue, fp) != NULL)
  {
    printf("La deuxieme ligne est : %s\n\n", tableaufinal + taille_lue);
  }
  else
  {
    fprintf(stderr, "Erreur lors de la lecture de la deuxieme ligne\n");
    return 1;
  }

  printf("Le contenu du buffer tableaufinal est :\n%s\n", tableaufinal);

  // atexit() interceptera ce return et exécutera 'nettoyer_fichier_temporaire'
  return 0;
}
