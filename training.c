#include <stdio.h>
#include <stdlib.h>

#define SECS_PER_MIN 60
#define SECS_PER_HOUR 3600

int x, y;
int main()
{
  int status;

  do
  {
    printf("\nEntrez une valeur entière pour x : : ");
    status = scanf("%d", &x);
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
      ;
    if (status != 1)
    {
      printf("Saisie invalide. Veuillez recommencer.\n");
    }
  } while (status != 1);

  do
  {
    printf("\nEntrez une valeur entière pour y : : ");
    status = scanf("%d", &y);
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
      ;
    if (status != 1)
    {
      printf("Saisie invalide. Veuillez recommencer.\n");
    }
  } while (status != 1);

  if (x == y)
    printf("x et y sont égaux\n");

  if (x > y)
    printf("x est plus grand que y\n");

  if (x < y)
    printf("x est plus petit que y\n");

  exit(EXIT_SUCCESS);
}