/*
 * Exemple de deux instruction for imbriquées
 */

#include <stdio.h>
#include <stdlib.h>

int count;

int main()
{
  count = 1;
  while (count <= 20)
  {
    printf("%d\n", count);
    count++;
  }
  return 0;
}