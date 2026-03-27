/*
* Nom du programme : week1.c
* Ce programme permet de saisir l'age et le revenu
* de 100 personnes au maximum. Il affihce ensuite
* les resultats obtenus
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 100
#define OUI 1
#define NON 0

long revenu[MAX];
int mois[MAX], jour[MAX], annee[MAX];

int x,y,ctr;
int cont;
long total_mois, grand_total;

int affiche_instructions(void);
void lecture(void);
void affiche_result(void);
int continuer(void);

int main(void) {
  cont = affiche_instructions();

  if (cont == OUI) {
    lecture();
    affiche_result();
  }else 
    printf("\nProgramme interrompu pa l'utilisateur !\n\n");
    exit(EXIT_SUCCESS);
}

int affiche_instructions(void) {
  printf("\n\n");
  printf("\nCe programme vous permet de saisir le revenu et");
  printf("\nla date de naissance de 99 personnes maxi, pour");
  printf("\ncalculer et afficher le total des revenus mois par mois,");
  printf("\nle total annuel des revenus, et la moyenne de ces revenus.");
  printf("\n");

  cont =continuer();
  return cont;
}

void lecture(void) {
  for (cont = OUI, ctr =0; ctr<MAX && cont == OUI; ctr++) {
    printf("\nENtrez les informations pour la personne no %d", ctr+1);
    printf("\n\ntDate de naissance :");

    do {
      printf("\n\tMois (0-12) :");
      scanf("%d", &mois[ctr]);
    }while (mois[ctr] < 0 || mois[ctr] > 12);

    do {
      printf("\n\tJour (1-31) :");
      scanf("%d", &jour[ctr]);
    }while (jour[ctr] < 1 || jour[ctr] > 31);

    do {
      printf("\n\tAnnee (0-1994) :");
      scanf("%d", &annee[ctr]);
    }while (annee[ctr] < 0 || annee[ctr] > 1944);
    printf("\nEntrez le revenu annuel :");
    scanf("%ld", &revenu[ctr]);

    cont =continuer();
  }
}

void affiche_result() {
  grand_total = 0;
  printf("\n\n\n");
  printf("\n    Salaires");
  printf("\n    ========");

  for(x=0; x<=12; x++) {
    total_mois = 0;
    for(y=0; y<ctr; y++) {
      if (mois[y] == x)
        total_mois = total_mois + revenu[y];
    }
    printf("\nLe total pour le mois %d est %ld", x, total_mois);
    grand_total += total_mois;
  }
  printf("\n\n\nLe total des revenus est de %ld", grand_total);
  printf("\nLa moyenne des revenus est de %ld", grand_total/ctr);  

  printf("\n\n***fin des resultats***");
}

int continuer(void) {
  printf("\nnVOulez vous continuer? (0=non / 1=oui) :");
  scanf("%d", &x);

  while (x<0 || x>1) {
    printf("\n%d est erroné !", x);
    printf("\nEntrez 0 pour sortier ou 1 pour continuer :");
    scanf("%d", &x);
  }
  if (x ==0)
  return NON;
  else
  return OUI;
}
