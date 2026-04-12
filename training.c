#include <stdio.h>
struct data
{
  int membre1;
  float membre2, membre3;
};

struct data info = {
    100,
    2,
    3.6};

struct data *ptr = &info;

int main()
{
  (*ptr).membre1 = 10;
  printf("%d", (*ptr).membre1);
  return 0;
}