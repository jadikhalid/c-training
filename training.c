/*
 * Exemple de déplacement dans un
 * tableau de structures
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX 4

struct part
{
  int nombre;
  char nom[10];
} data[MAX] = {
    {1, "smith"},
    {2, "Jones"},
    {3, "Adams"},
    {4, "Wilson"}};

struct part *p_part;
int count;

int main()
{
  p_part = data;

  for (count = 0; count < MAX; count++)
  {
    printf("A l'adresse %p : %d %s\n", (void *)p_part, p_part->nombre, p_part->nom);
    p_part++;
  }
  exit(EXIT_SUCCESS);
}
