/*
 * xemple typique d'utilisation d'une union
 */

#include <stdio.h>
#include <stdlib.h>

#define CARACTERE 'C'
#define INTEGER 'I'
#define FLOAT 'F'

struct generic_tag
{
  /* data */
  char type;
  union shared_tag
  {
    /* data */
    char c;
    int i;
    float f;
  } shared;
};

void print_fonction(struct generic_tag generic);

int main()
{
  struct generic_tag var;

  var.type = CARACTERE;
  var.shared.c = '$';
  print_fonction(var);

  var.type = FLOAT;
  var.shared.f = (float)12345.67890;
  print_fonction(var);

  var.type = 'x';
  var.shared.i = 111;
  print_fonction(var);

  return 0;
}

void print_fonction(struct generic_tag generic)
{
  printf("\nLa valeur generique est ...");
  switch (generic.type)
  {
  case CARACTERE:
    printf("%c", generic.shared.c);
    break;

  case INTEGER:
    printf("%d", generic.shared.i);
    break;

  case FLOAT:
    printf("%f", generic.shared.f);
    break;

  default:
    printf("de type inconnu : %c\n", generic.type);
    break;
  }
}
