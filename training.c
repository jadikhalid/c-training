/*
 * Programme de tri de phrases
 * Amélioré : Gestion mémoire, sécurité et algorithme de tri standard.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utilitaires.h"

#define MAXLINES 25
#define BUFSIZE 80

// Prototypes
int get_lines(char *lines[], int max_lines);
void print_strings(char *p[], int n);
void free_lines(char *lines[], int n);
int compare_strings(const void *a, const void *b);

int main(void)
{
  char *lines[MAXLINES];
  int number_of_lines;

  number_of_lines = get_lines(lines, MAXLINES);

  if (number_of_lines < 0)
  {
    fprintf(stderr, "Erreur fatale : échec d'allocation mémoire.\n");
    return EXIT_FAILURE;
  }

  if (number_of_lines > 0)
  {
    qsort(lines, (size_t)number_of_lines, sizeof(char *), compare_strings);

    printf("\n--- Phrases triées ---\n");
    print_strings(lines, number_of_lines);

    // 3. LIBÉRATION de la mémoire (Indispensable pour la perfection)
    free_lines(lines, number_of_lines);
  }
  else
  {
    puts("Aucune phrase saisie.");
  }

  return EXIT_SUCCESS;
}

int get_lines(char *lines[], int max_lines)
{
  int n = 0;
  char buffer[BUFSIZE];

  puts("Tapez vos phrases (Entrée vide pour terminer) :");

  while (n < max_lines && lire_clavier(buffer, sizeof(buffer)) != 0)
  {
    if (buffer[0] == '\0')
      break;

    lines[n] = malloc(strlen(buffer) + 1);
    if (lines[n] == NULL)
    {
      free_lines(lines, n); // On nettoie ce qui a déjà été alloué avant de quitter
      return -1;
    }

    strcpy(lines[n], buffer);
    n++;
  }
  return n;
}

// Fonction de comparaison pour qsort
// On caste les pointeurs génériques (void*) en pointeurs de pointeurs de char
int compare_strings(const void *a, const void *b)
{
  const char *str_a = *(const char **)a;
  const char *str_b = *(const char **)b;
  return strcmp(str_a, str_b);
}

void print_strings(char *p[], int n)
{
  for (int i = 0; i < n; i++)
  {
    printf("[%d]: %s\n", i + 1, p[i]);
  }
}

// La fonction qui manquait pour "nettoyer" la RAM
void free_lines(char *lines[], int n)
{
  for (int i = 0; i < n; i++)
  {
    free(lines[i]);
    lines[i] = NULL; // Bonne pratique : éviter les pointeurs fous
  }
}