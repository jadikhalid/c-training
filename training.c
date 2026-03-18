#include <stdio.h>
#include <stdlib.h>

#define GRAMMES_PAR_LIVRE 454
const int DEBUT_SIECLE = 2000;

int poids_en_grammes, poids_en_livres;
int an_naissance, age_en_2000;

int main()
{
  printf("Entrez votre poids en livres :");
  scanf("%d", &poids_en_livres);
  printf("Entrez votre an de naissance :");
  scanf("%d", &an_naissance);

  poids_en_grammes = poids_en_livres * GRAMMES_PAR_LIVRE;
  age_en_2000 = DEBUT_SIECLE - an_naissance;

  printf("Poids en livres : %d\n", poids_en_livres);
  printf("Poids en grammes : %d\n", poids_en_grammes);
  printf("An de naissance : %d\n", an_naissance);
  printf("Age en 2000 : %d\n", age_en_2000);
  exit(EXIT_SUCCESS);
}