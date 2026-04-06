#include <stdio.h>
#include <stdlib.h>

int longuer, largeur;
long aire;

struct coord{
      int x;
      int y;
};

struct rectangel {
      struct coord hautgauche;
      struct coord basdroite;
} maboite;

int main() {
      printf("\nEntrez la coordonnée x du coin superieur gauche de la boite : ");
      scanf("%d", &maboite.hautgauche.x);

      printf("\nEntrez la coordonnée y du coin superieur gauche de la boite : ");
      scanf("%d", &maboite.hautgauche.y);

      printf("\nEntrez la coordonnée x du coin inferieur droit de la boite : ");
      scanf("%d", &maboite.basdroite.x);

      printf("\nEntrez la coordonnée y du coin inferieur droit de la boite : ");
      scanf("%d", &maboite.basdroite.y);

      /* Calcul et affichage de l'aire */
      longuer = maboite.basdroite.x - maboite.hautgauche.x;
      largeur = maboite.hautgauche.y - maboite.basdroite.y;
      aire = longuer * largeur;
      printf("\nL'aire de la boite est : %ld\n", aire);
      return 0;   
}