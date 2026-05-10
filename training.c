/* ==============================================*
 * Program : list1513.c
 * Objectif : Implémenter une liste chaînée
 *===============================================*/

#include <stdio.h>
#include <stdlib.h>

/* Structure d'un maillon */
struct list
{
  int ch;
  struct list *next_rec;
};

/* Les typedef pour la structure et son pointeur */
typedef struct list LIST;
typedef LIST *LISTPTR;

/* Prototypes des fonctions */
LISTPTR add_to_list(int, LISTPTR);
void show_list(LISTPTR);
void free_memory_list(LISTPTR);

int main()
{
  LISTPTR first = NULL;
  int i = 0;
  int ch;
  char trash[256];

  while ((i++ < 5))
  {
    ch = 0;
    printf("\nEntrez un caractère %d, ", i);

    do
    {
      printf("\nvaleurs entre a et z , svp: ");
      ch = getc(stdin);
      fgets(trash, sizeof(trash), stdin);
    } while ((ch < 'a' || ch > 'Z') && (ch < 'A' || ch > 'Z'));
    first = add_to_list(ch, first);
  }

  show_list(first);

  free_memory_list(first);

  return 0;
}
