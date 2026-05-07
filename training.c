/*
 * Tri d'une suite de lignes de texte - Version Sécurisée
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utilitaires.h"

#define MAXLINES 25
#define TOUJOURS 1

// Prototypes avec protection 'const' pour strcmp
int get_lines(char *lines[]);
void sort(char *p[], int n, int sort_type);
void print_strings(char *p[], int n);
int alpha(char *p1, char *p2);
int reverse(char *p1, char *p2);

// Tableau de pointeurs global (initialisé à NULL par défaut)
char *lines[MAXLINES] = {NULL};

int main()
{
  int number_of_lines, sort_type, c;

  number_of_lines = get_lines(lines);

  // Cas d'erreur d'allocation (déjà nettoyé dans get_lines)
  if (number_of_lines < 0)
  {
    fprintf(stderr, "Erreur fatale : allocation mémoire impossible\n");
    return 1;
  }

  // Si aucune ligne n'a été saisie
  if (number_of_lines == 0)
  {
    puts("Aucune donnée à trier.");
    return 0;
  }

  while (TOUJOURS)
  {
    printf("\n--- Options de tri ---\n");
    printf("0 : Ordre alphabétique inverse (Z -> A)\n");
    printf("1 : Ordre alphabétique direct  (A -> Z)\n");
    printf("Votre choix : ");

    if (scanf("%d", &sort_type) != 1)
    {
      puts("Erreur : Veuillez entrer un nombre (0 ou 1).");
      // Nettoyage complet du buffer d'entrée
      while ((c = getchar()) != '\n' && c != EOF)
        ;
      continue;
    }

    if (sort_type != 0 && sort_type != 1)
    {
      puts("Erreur : Choix hors limites.");
      continue;
    }

    // Exécution du tri et affichage
    sort(lines, number_of_lines, sort_type);
    print_strings(lines, number_of_lines);

    break; // Sortie du programme après un tri réussi
  }

  // --- NETTOYAGE FINAL DE LA MÉMOIRE ---
  for (int i = 0; i < number_of_lines; i++)
  {
    if (lines[i] != NULL)
    {
      free(lines[i]);
      lines[i] = NULL;
    }
  }

  return 0;
}

int get_lines(char *lines[])
{
  int n = 0;
  char buffer[80];

  puts("Tapez vos lignes (Entrée vide pour terminer) :");

  // lire_clavier doit utiliser sizeof(buffer) pour éviter le buffer overflow
  while (n < MAXLINES && lire_clavier(buffer, sizeof(buffer)) != 0)
  {
    lines[n] = malloc(strlen(buffer) + 1);

    if (lines[n] == NULL)
    {
      // Rollback : On libère tout ce qui a été fait avant de quitter
      for (int j = 0; j < n; j++)
      {
        free(lines[j]);
        lines[j] = NULL;
      }
      return -1;
    }
    strcpy(lines[n++], buffer);
  }
  return n;
}

void sort(char *p[], int n, int sort_type)
{
  // Protection contre les arguments invalides
  if (p == NULL || n < 2)
    return;

  int a, b;
  char *temp;
  int (*compare)(char *s1, char *s2);

  // 1 = alpha (A-Z), 0 = reverse (Z-A)
  compare = (sort_type == 1) ? alpha : reverse;

  // Tri à bulles optimisé
  for (a = 0; a < n - 1; a++)
  {
    for (b = 0; b < n - 1 - a; b++)
    {
      // On s'assure que les pointeurs à comparer ne sont pas NULL
      if (p[b] && p[b + 1] && compare(p[b], p[b + 1]) > 0)
      {
        temp = p[b];
        p[b] = p[b + 1];
        p[b + 1] = temp;
      }
    }
  }
}

void print_strings(char *p[], int n)
{
  if (p == NULL)
    return;

  printf("\n--- Liste Triée ---\n");
  for (int count = 0; count < n; count++)
  {
    if (p[count] != NULL)
      printf("[%d] %s\n", count + 1, p[count]);
  }
}

// Logique rectifiée pour correspondre aux noms
int alpha(char *p1, char *p2)
{
  return strcmp(p1, p2); // Renvoie > 0 si p1 > p2 (ex: 'B' > 'A')
}

int reverse(char *p1, char *p2)
{
  return strcmp(p2, p1); // Inverse le résultat de strcmp
}