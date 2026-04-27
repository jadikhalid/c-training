/*
 * Nettoyage de stdin
 */

#include <stdio.h>
#include <stdlib.h>

void clear_kb(void);

int main()
{
  int age = -999;
  char nom[20];

  puts("Entrez votre âge :");
  if (scanf("%u", &age) != 1)
  {
    puts("Erreur de saisie pour l'âge.");
  }

  clear_kb();

  puts("Entrez votre nom :");
  scanf("%19s", nom);

  printf("Vous avez %d ans\n", age);
  printf("Vous vous appelez %s\n", nom);

  return 0;
}

void clear_kb(void)
{
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}