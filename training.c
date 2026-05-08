/*
 * Illustre les operations de base
 * dans une liste chainee
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct data
{
  char name[20];
  struct data *next;
};

typedef struct data PERSON;
typedef PERSON *LINK;

int main()
{
  LINK head = NULL;
  LINK new = NULL;
  LINK current = NULL;

  new = malloc(sizeof(PERSON));
  new->next = head;
  head = new;
  strcpy(new->name, "Abigail");
  /*to be continue...*/
}
