/*
* Exemple de plusieurs instructions return
*/

#include <stdio.h>
#include <stdlib.h>

int x,y,z;
int larger_of(int a, int b);

int main () {
  puts("Entrez deux valeurs entieres diiférentes : ");
  scanf("%d%d", &x, &y);

  z=larger_of(x,y);

  printf("\nLa valeur la plus grande est %d.", z);
  return 0;
}

int larger_of(int a, int b) {
  if (a>b) return a;
  else return b;
}