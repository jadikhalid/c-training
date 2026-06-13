/* Emploi de memset, memcpy et memmove */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char message1[60] = "le chene, un jour, dit au roseau";
char message2[60] = "abcdefghijklmnopqrstuvwxyz";
char tempon[60];

int main()
{
  printf("\nmessage[1] avant memset : \t%s", message1);
  memset(message1 + 5, '0', 10);
  printf("\nmessage[1] apres memset : \t%s", message1);

  strcpy(tempon, message2);
  printf("\n\nmessage original : %s", tempon);
  memcpy(tempon + 4, tempon + 16, 10);
  printf("\nApres memcpy, sans recouvrement : \t%s", tempon);
  strcpy(tempon, message2);
  memmove(tempon + 6, tempon + 4, 10);
  printf("\nApres memcpy avec recouvrement : \t%s", tempon);

  strcpy(tempon, message2);
  printf("\n\nMessage original : %s", tempon);
  memmove(tempon + 4, tempon + 16, 10);
  printf("\nAprès memmove() sans recouvrement :\t%s", tempon);
  strcpy(tempon, message2);
  memmove(tempon + 6, tempon + 4, 10);
  printf("\nAprès memmove() avec recouvrement :\t%s\n", tempon);

  return 0;
}