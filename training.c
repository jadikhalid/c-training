#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char tableau1[] = "Hello, World!";
char tableau2[20];

char *d = tableau2;

int main() {
   for (char *p = tableau1; *p != '\0'; p++) {
         *d = *p;
         d++;
   } 
   *d = '\0'; // Null-terminate the second string
   printf("Tableau 1: %s\n", tableau1);
   printf("Tableau 2: %s\n", tableau2);
    return 0;
}