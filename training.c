/*
* Nature numérique des variables char
*/

#include <stdio.h>
#include <stdlib.h>

unsigned char x;

int main() {
   for (x=180; x<204; x++) {
    printf("%c = %d\n", x, x);
   }
}