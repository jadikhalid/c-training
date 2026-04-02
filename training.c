#include <stdio.h>
#include <stdlib.h>

char lmom[81], fnom[81];
int count, id_num;

int main() {
   puts("Entrez votre nom, prenom et matricule separes");
   puts("par des espaces et appuyez sur entrée");

   count = scanf("%80s%80s%d", lmom, fnom, &id_num);

   printf("%d", count);

   return 0;
}