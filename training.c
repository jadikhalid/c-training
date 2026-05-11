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
    } while ((ch < 'a' || ch > 'z') && (ch < 'A' || ch > 'Z'));
    first = add_to_list(ch, first);
  }

  show_list(first);

  free_memory_list(first);

  return 0;
}

/*==================================================*
* Fonction add_to_list()
* BUt : Insérer un nouveau maillon dans la liste
* Entrée : int ch = cqrqctère à insérer
           LISTPTR first = adresse du pointeur de tête
* Retour : Adresse du pointeur de tête (first)
=====================================================*/

LISTPTR add_to_list(int ch, LISTPTR first)
{
  LISTPTR new_rec = malloc(sizeof(LIST));
  if (!new_rec)
  {
    printf("Mémoire insuffisante!\n");
    exit(EXIT_FAILURE);
  }
  new_rec->ch = ch;
  new_rec->next_rec = NULL;

  // Cas 1 : La liste est vide OU le nouvel élément doit devenir la nouvelle TÊTE
  if (first == NULL || ch < first->ch)
  {
    new_rec->next_rec = first;
    return new_rec; // Le nouveau maillon devient le début
  }

  // Cas 2 : Insertion au milieu ou à la fin
  LISTPTR current = first;
  // On cherche le maillon après lequel on doit insérer
  while (current->next_rec != NULL && current->next_rec->ch < ch)
  {
    current = current->next_rec;
  }

  // On insère entre 'current' et 'current->next_rec'
  new_rec->next_rec = current->next_rec;
  current->next_rec = new_rec;

  return first;
}

// LISTPTR add_to_list(int ch, LISTPTR first)
// {
//   LISTPTR new_rec = NULL;
//   LISTPTR tmp_rec = NULL;
//   LISTPTR prev_rec = NULL;

//   /*Allocation mémoire*/
//   new_rec = malloc(sizeof(LIST));
//   if (!new_rec) /*Au cas oû il n y a plus de mémoire*/
//   {
//     printf("Mémoire insuffisante!\n");
//     exit(EXIT_FAILURE);
//   }

//   /*Chîner les données*/
//   new_rec->ch = ch;
//   new_rec->next_rec = NULL;

//   if (first == NULL) /*Ajout du premier élément à la liste*/
//   {
//     first = new_rec;
//     new_rec->next_rec = NULL;
//   }
//   else
//   {
//     tmp_rec = first->next_rec;
//     prev_rec = first;

//     if (tmp_rec == NULL)
//     {
//       prev_rec->next_rec = new_rec;
//     }
//     else
//     {
//       while ((tmp_rec->next_rec != NULL))
//       {
//         if (new_rec->ch < tmp_rec->ch)
//         {
//           new_rec->next_rec = tmp_rec;
//           if (new_rec->next_rec != prev_rec->next_rec)
//           {
//             printf("Erreur");
//             getc(stdin);
//             return 0;
//           }
//           prev_rec->next_rec = new_rec;
//           break;
//         }
//         else
//         {
//           tmp_rec = tmp_rec->next_rec;
//           prev_rec = prev_rec->next_rec;
//         }
//       }

//       if (tmp_rec->next_rec == NULL)
//       {
//         if (new_rec->ch < tmp_rec->ch)
//         {
//           new_rec->next_rec = tmp_rec;
//           prev_rec->next_rec = new_rec;
//         }
//         else
//         {
//           tmp_rec->next_rec = new_rec;
//           new_rec->next_rec = NULL;
//         }
//       }
//     }
//   }

//   return (first);
// }

/*==================================================*
* Fonction : show list
But : Affiche le contenu de la liste chaînée
====================================================*/

void show_list(LISTPTR first)
{
  LISTPTR cur_ptr;
  int counter = 1;

  printf("\n\nAdr élém Position Val. Adr élém suivant\n");
  printf("========== ======== ==== ================\n");

  cur_ptr = first;
  while (cur_ptr != NULL)
  {
    printf("  %p", cur_ptr);
    printf(" %2i  %c", counter++, cur_ptr->ch);
    printf("  %p \n", cur_ptr->next_rec);
    cur_ptr = cur_ptr->next_rec;
  }
}

/*=====================================================*
* Fonctioàn : free_memory_list
* But : libère la totalité de la mémoire acquise
=======================================================*/
void free_memory_list(LISTPTR first)
{
  LISTPTR cur_ptr, next_rec;
  cur_ptr = first;

  while (cur_ptr != NULL)
  {
    next_rec = cur_ptr->next_rec;
    free(cur_ptr);
    cur_ptr = next_rec;
  }
}