#include <stdio.h>

int main()
{
  char tableau[12][12];
  char (*ptr)[12] = tableau;
  for (int i = 0; i < 12; i++)
  {
    for (int j = 0; j < 12; j++)
    {
      *(*(ptr + i) + j) = 'X';
      printf("%c ", *(*(ptr + i) + j));
    }
    printf("\n");
  }

  return 0;
}
