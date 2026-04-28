#include <stdio.h>
#include <stdlib.h>

#define MAXSTRING 80

char message[] = "Affiché avec putchar().";
int main()
{
  int count;
  for (count = 0; count < MAXSTRING; count++)
  {
    if (message[count] == '\0')
    {
      putchar('\n');
      break;
    }
    else
      putchar(message[count]);
  }
  return 0;
}