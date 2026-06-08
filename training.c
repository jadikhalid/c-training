/* Focntions avec un nombre variables d'arguments */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

float moyenne(int num, ...);

int main()
{
  float x;
  x = moyenne(10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
  printf("\nLa premiere moyenne est %f.", x);

  x = moyenne(5, 121, 44, 57, 3, 66);
  printf("\nLa deuxieme moyenne est %f.", x);

  return 0;
}

float moyenne(int num, ...)
{
  /* Déclarer une variable de type va_list */
  va_list arg_ptr;
  int count, total = 0;

  /* Initialiser le pointeur vers les arguments */
  va_start(arg_ptr, num);

  /* Récupérer chaque argument de la liste des variables */
  for (count = 0; count < num; count++)
    total += va_arg(arg_ptr, int);

  /* Donner un coup de nalai */
  va_end(arg_ptr);

  /* resultat */
  return ((float)total / num);
}