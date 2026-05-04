/*
 * Passer un tableau a plusieurs dimensions
 * a une fonction au moyen d un pointeur
 */

#include <stdio.h>
#include <stdlib.h>

void printarray_1(int (*ptr)[4]);
void printarray_2(int (*ptr)[4], int n);

int main()
{
  int multi[3][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};

  int (*ptr)[4], count;

  ptr = multi;

  for (count = 0; count < 3; count++)
  {
    printarray_1(ptr++);
  }

  puts("\n\nAppuyez sur entrée...");
  getchar();
  printarray_2(multi, 3);
  printf("\n");

  return 0;
}

void printarray_1(int (*ptr)[4])
{
  int *p, count;
  p = (int *)ptr;

  for (count = 0; count < 4; count++)
  {
    printf("\n%d", *p++);
  }
}

void printarray_2(int (*ptr)[4], int n)
{
  int *p, count;
  p = (int *)ptr;

  for (count = 0; count < (4 * n); count++)
    printf("\n%d", *p++);
}
