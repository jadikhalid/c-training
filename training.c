/*
* 
*/

#include <stdio.h>
#include <stdlib.h> 

int tab[12][10];

int main() {
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 10; j++) {
            tab[i][j] = rand();
        }
    }

    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 10; j++) {
            printf("%d ", tab[i][j]);
        }
        printf("\n");
    }

    return 0;
}
