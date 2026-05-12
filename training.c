#include <stdio.h>

/*Prototype de fonctions */
char fonction(char *tableau[]);
char (*ptr)(char *[]) = fonction;

int main()
{
  int tableau[2][3][4];
  size_t taille = sizeof(tableau);

  printf("%zu\n", taille);

  return 0;
}
