#include <stdio.h>
#include <stdlib.h>

char input[81];

int main() {
   puts("Saisissez votre texte, puis qppuyez uer ENtree");
   fgets(input, sizeof(input), stdin);
   printf("Vous avez saisi : %s\n", input);

   exit(EXIT_SUCCESS);
}