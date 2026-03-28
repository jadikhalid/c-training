/*
* Tableau a 1000 valeurs
*/

#include <stdio.h>
#include <stdlib.h>

int random[10][10][10];
int a,b,c;

int main() {
  for (a=0; a<10; a++) {
    for (b=0; b<10; b++) {
      for (c=0; c<10; c++) {
        random[a][b][c] = rand();
      }
    }
  }

  for (a=0; a<10; a++) {
    for (b=0; b<10; b++) {
      for (c=0; c<10; c++) {
        printf("[%d][%d][%d] = ", a, b, c);
        printf("%d\n", random[a][b][c]);
      }
      printf("\nAppuyez sur Entrée pour continuer et CRTL-C pour sortir.");
      getchar();
    }
    printf("\n");
  }


  return 0;
  }