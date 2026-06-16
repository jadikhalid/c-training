#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "utilitaires.h"

// Definition de constantes
#define OUI 1
#define NON 0
#define REC_LENGTH 54

// Definition de variables
struct record
{
  char fname[16];
  char lname[21];
  char mname[11];
  char phone[10];
} rec;

// Prototypes des fonctions
int main(int argc, char *argv[]);
void display_usage(char *filename);
int display_menu(void);
void get_data(FILE *fp, char *progname, char *filename);
// void display_report(FILE *fp);
int continue_function(void);
// int look_up(FILE *fp);

// Point d'entrée
int main(int argc, char *argv[])
{
  FILE *fp;
  int cont = OUI;

  if (argc < 2)
  {
    display_usage("SEMAINE3");
    return 1;
  }

  if ((fp = fopen(argv[1], "a+")) == NULL)
  {
    fprintf(stderr, "%s(%d)--Erreur a l ouverture du fichier %s", argv[0], __LINE__, argv[1]);
    return 1;
  }

  while (cont == OUI)
  {
    switch (display_menu())
    {
    case '1':
      get_data(fp, argv[0], argv[1]);
      break;

    default:
      break;
    }
  }

  return 0;
}

// Definitions  des fonctions
// display_usage
void display_usage(char *filename)
{
  printf("\n\nUSAGE : %s nom de fichier", filename);
  printf("\n\n  ou \"nom de fichier\" est le nom du fichier annuaire\n");
}
// display_menu
int display_menu(void)
{
  char ch, buf[20];
  printf("\n");
  printf("\n      MENU");
  printf("\n    ========\n");
  printf("\n1.   Entrée de noms");
  printf("\n2.   Affichage liste");
  printf("\n3.   Recherche numéro");
  printf("\n4.   Quitter");
  printf("\n\nTapez votre choix ==> ");
  lire_clavier(buf, sizeof(buf));
  ch = *buf;
  return (ch);
}
// get_data
void get_data(FILE *fp, char *progname, char *filename)
{
  int cont = OUI;
  while (cont == OUI)
  {
    printf("\n\nIndiquez ci-apres les renseignements :");
    printf("\n\nPreno : ");
    lire_clavier(rec.fname, sizeof(rec.fname));
    printf("\nNom de famille :");
    lire_clavier(rec.lname, sizeof(rec.lname));
    printf("\nNumero de telephone :");
    lire_clavier(rec.phone, sizeof(rec.phone));

    if (fseek(fp, 0, SEEK_END) == 0)
      if (fwrite(&rec, 1, sizeof(rec), fp) != sizeof(rec))
      {
        fprintf(stderr, "%s(%d)--Erreur en ecriture sur le fichier %s", progname, __LINE__, filename);
        return 1;
      }
    cont = continue_function();
  }
}
// continue_function
