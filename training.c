/*
 * Exemple de variables locales statiques et automatiques
 */

#include <stdio.h>
#include <stdlib.h>

void fonc1(void);

int main()
{
  int count;

  for (count=0; count<20;count++){
    printf("Iteration numero %d", count);
    fonc1();
  }

  exit(EXIT_SUCCESS);
}


void fonc1(void) {
  static int x =0;
  int y = 0;

  printf("x = %d, y = %d\n", x++, y++);
}
