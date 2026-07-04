#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifdef OPTIONS_LONGUES
#include <getopt.h>
#endif

/* Definition des valeurs par défaut*/
#define ADRESSE_SERVEUR_DEFAUT "localhost"
#define PORT_SERVEUR_DEFAUT "4000"
#define CONNEXION_AUTO_DEFAUT 0
#define DELAI_CONNEXION_DEFAUT 4

void sous_option(char *ssopt, int *cnx_auto, int *delai);

void suite_application(char *adresse_serveur,
                       char *port_serveur,
                       int connexion_auto,
                       int delai_reconnexion,
                       int argc, char *argv[]);

void affiche_aide(char *nom_programme);

int main(int argc, char *argv[])
{
  /* Copie des chaines d'environnement */
  char *opt_adr = NULL;
  char *opt_sry = NULL;
  int opt_delai = 0;
  char *retour_getenv;

  /* Variables contenant les valeurs effectives de nos paramètres */
  static char *adresse_serveur = ADRESSE_SERVEUR_DEFAUT;
  static char *port_serveur = PORT_SERVEUR_DEFAUT;
  int connexion_auto = CONNEXION_AUTO_DEFAUT;
  int option;

  /* Lecture des varibales d'environnement */
  retour_getenv = getenv("OPT_ADR");
  if ((retour_getenv != NULL) && (strlen(retour_getenv) != 0))
  {
    opt_adr = (char *)malloc(strlen(retour_getenv) + 1);
    if (opt_adr != NULL)
    {
      strcpy(opt_adr, retour_getenv);
      adresse_serveur = opt_adr;
    }
    else
    {
      perror("malloc");
      exit(1);
    }
  }
}