#include <stdio.h>
#include <string.h>
int main() {
      const char chaine1[] = "Hello, World! My name is John.";
      const char chaine2[] = "Welcome to C programming.";

      size_t len1 = strlen(chaine1);
      size_t len2 = strlen(chaine2);

      printf("Length of chaine1: %zu\n", len1);
      printf("Length of chaine2: %zu\n", len2);

      if (len1 != len2) {
            const char *p = (len1 > len2) ? chaine1 : chaine2;
            printf("The longer string is: %s\n", p);
      } else {
            printf("Both strings have the same length.\n");
      }

      return 0;
}

