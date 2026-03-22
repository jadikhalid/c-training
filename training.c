/*Programme : trouver_nombre.c
* Objectif : Ce programme choisit un nombre de facon aléatoire
*            et demmade l'utilisateur de le trouver
* Retour : aucun
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NO 0
#define YES (!NO)

int main(void) {
  int guess_Value = -1;
  int nombre;
  int nbr_of_gueses;
  int done = NO;

  printf("Selection d'un nombre aleatoire\n");
  srand(time(NULL));
  nombre = rand();

  nbr_of_gueses = 0;
  while (done == NO) {
    printf("\nDonnez un nombre entre 0 et %d\n", RAND_MAX);
    scanf("%d", &guess_Value);
    nbr_of_gueses++;
    if(nombre == guess_Value) {
      done = YES;
    }else {
      nombre<=guess_Value ? printf("Trop grand\n") : printf("Trop petit\n");
    }
}

printf("\nVous avez trouve en %d essais\n", nbr_of_gueses);
printf("Le nombre etait %d\n", nombre);
return 0;
}