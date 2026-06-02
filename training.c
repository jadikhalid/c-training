/* La fonction strcat() */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char str1[] = "a";
char str2[2];

int main()
{
  str2[1] = '\0';
  for (int n = 98; n < 123; n++)
  {
    str2[0] = n;
    strcat(str1, str2);
    puts(str1);
  }

  return 0;
}