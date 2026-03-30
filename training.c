/*
* passer un tableau a une fonction
* en tant qu'argument : pointeur+taille
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 10

int tab[MAX], count;

int largest(int x[], int y);

int main () {
    for (count=0; count<MAX; count++) {
        printf("Entrez un entier : ");
        scanf("%d", &tab[count]);}

        printf("\n\nLa valeur la lus grande est : %d\n ", largest(tab, MAX));

        return 0;
    
}

int largest(int x[], int y) {
    int count, biggest=x[0];

    for(count=1; count < y; count++)
        if (x[count] > biggest)
            biggest = x[count];
    return biggest;

}