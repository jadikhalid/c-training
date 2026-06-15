/* Entrer un nombre et afficher son carré */
#include <stdio.h>
#include <stdlib.h>
#include "calc.h"

int main()
{
  int x;
  printf("Tapez un nombre entier : ");
  scanf("%d", &x);
  printf("\nLe carré de %d est %ld", x, sqr(x));

  return 0;
}