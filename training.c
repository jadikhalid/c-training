/*
* Exemple d'utilisation de la fonction scanf()
*/

#include<stdio.h>
#include <stdlib.h>

#define QUIT 4

int choix_menu(void);

int main () {
  int choix =0;
  int var_int = 0;
  float var_float =0.0;
  unsigned var_unsigned = 0;

  while (choix != QUIT){
    choix = choix_menu();
    if (choix ==1) {
      puts("\nEntrez un entier décimal signé (ex -123)");
      scanf("%d", &var_int);
    }
    if (choix ==2) {
      puts("\nEntrez un nombre avec virgule flotante (ex 1.23)");
      scanf("%f", &var_float);
    }
    if (choix ==3) {
      puts("\nEntrez un nombre entier non signé (ex 123)");
      scanf("%u", &var_unsigned);
    }
  }
  printf("\nVos valeurs sont : int: %d float :%f unsigner : %u\n", var_int, var_float, var_unsigned);
  return 0;
}

int choix_menu(void){
  int selection =0;

  do {
    puts("\n1- Lire un entier décimal signé");
    puts("2- Lire un nombre avec virgule flotante");
    puts("3- Lire un entier décimal non signé");
    puts("4- Quitter\n");
    puts("Votre choix : ");
    scanf("%d", &selection);
  } while (selection < 1 || selection > QUIT);
  

  return selection;
}