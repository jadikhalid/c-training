/*
 * Tri d'une suite ce lignes de texte
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 25
#define TOUJOURS 1

int get_lines(char *lines[]);
void sort(char *p[], int n, int sort_type);
void print_strings(char *p[], int n);
int alpha(char *p1, char *p2);
int reverse(char *p1, char *p2);

char *lines[MAXLINES];

int main()
{
  int number_of_lines, sort_type, c;

  number_of_lines = get_lines(lines);

  if (number_of_lines < 0)
  {
    puts("Erreur d'allocation mémoire");
    return 1;
  }
  while (TOUJOURS)
  {
    printf("Tapez 0 pour trier en ordre alphabétique inverse,\n");
    printf("ou 1, pour trier en ordre alphabétique direct :");
    if (scanf("%d", sort_type) != 1)
    {
      puts("Erreur de saisie");

      while ((c = getchar != '\n'))
        ;
      continue;
    };
    sort(lines, number_of_lines, sort_type);
    print_strings(lines, number_of_lines);

    return 0;
  }
}