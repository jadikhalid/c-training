#include <stdio.h>
#include <stdlib.h>

int multi[2][4];

int main()
{
  printf("\nmulti = %p", (void *)multi);
  printf("\nmulti[0] = %p", (void *)multi[0]);
  printf("\nmulti[0][0] = %p", (void *)&multi[0][0]);

  return 0;
}