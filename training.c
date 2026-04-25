/*
 * Utilisation de getchar() pour lire
 * des chaines de caracteres
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX 80

int main()
{
  int ch;
  char buffer[MAX + 1];
  int x = 0;

  while ((ch = getchar()) != '\n' && ch != EOF && x < MAX)
    buffer[x++] = ch;

  buffer[x] = '\0';
  puts("Codes ASCII saisis :");
  printf("%s\n", buffer);
  for (int i = 0; i < x; i++)
  {
    printf("%c: %d ", buffer[i], buffer[i]);
  }

  return 0;
}