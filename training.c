// Bibliotheques systeme
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

// Bibliotheques prioritaires
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
void display_report(FILE *fp);
int continue_function(void);
int look_up(FILE *fp);

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
    case '2':
      display_report(fp);
      break;
    case '3':
      look_up(fp);
      break;
    case '4':
      printf("\n\nMerci d'avoir utilisé ce programme.\n");
      cont = NON;
      break;
    default:
      printf("\n\nChoix incorrect. Choisissez de 1 a 4.");
    }
  }
  fclose(fp);
  return 0;
}

// Définition de la fonction display_usage
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
// Définition de la fonction  get_data
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
        exit(EXIT_FAILURE);
      }
    cont = continue_function();
  }
}
// Définition de la fonction  continue_function
int continue_function(void)
{
  char ch, buf[20];
  do
  {
    printf("\n\nVoulez-vous saisir un autre ? (O)ui/(N)on.");
    lire_clavier(buf, sizeof(buf));
    ch = *buf;
  } while (strchr("NnOo", ch) == NULL);
  if (ch == 'n' || ch == 'N')
    return (NON);
  else
    return (OUI);
}
// Définition de la fonction  display_report
void display_report(FILE *fp)
{
  time_t rtime;
  int num_of_secs = 0;

  time(&rtime);
  fprintf(stdout, "\n\nHeure actuelle : %s", ctime(&rtime));
  fprintf(stdout, "\nAnnuaire téléphonique\n");

  if (fseek(fp, 0, SEEK_SET) == 0)
  {
    fread(&rec, 1, sizeof(rec), fp);
    while (!feof(fp))
    {
      fprintf(stdout, "\n\t%s, %s %c %s", rec.lname, rec.fname, rec.mname[0], rec.phone);
      num_of_secs++;
      fread(&rec, 1, sizeof(rec), fp);
    }
    fprintf(stdout, "\n\nNombre total d'enregistrements : %d", num_of_secs);
    fprintf(stdout, "\n\n* * * Affichage treminé * * * \n");
  }
  else
    fprintf(stderr, "\n\n * * * Erreur au cous de l'affichange * * *\n");
}
// Définition de la fonction  look_up
int look_up(FILE *fp)
{
  char tmp_lname[21];
  int ctr = 0;

  fprintf(stdout, "\n\nIndiquez le nom propre a rechercher : ");
  lire_clavier(tmp_lname, sizeof(tmp_lname));
  if (strlen(tmp_lname) != 0)
  {
    if (fseek(fp, 0, SEEK_SET) == 0)
    {
      fread(&rec, 1, sizeof(rec), fp);
      while (!feof(fp))
      {
        if (strcmp(rec.lname, tmp_lname) == 0)
        {
          fprintf(stdout, "\n%s %s %s - %s", rec.fname, rec.mname, rec.lname, rec.phone);
          ctr++;
        }
        fread(&rec, 1, sizeof(rec), fp);
      }
    }
    fprintf(stdout, "\n\n%d correspondance(s).", ctr);
  }
  else
    fprintf(stdout, "\nVous n'svez pas indiqué de nom.");
  return ctr;
}
