/*
 * Réalisation d'un menu systeme avec une boucle infinie
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int menu(void);

int main()
{
  int choix;

  while (1)
  {
    choix = menu();
    if (choix == 1)
    {
      puts("\nExécution de la tache correspondant au choix 1.");
      sleep(5);
    }
    else if (choix == 2)
    {
      puts("\nExécution de la tache correspondant au choix 2.");
      sleep(5);
    }
    else if (choix == 3)
    {
      puts("\nExécution de la tache correspondant au choix 3.");
      sleep(5);
    }
    else if (choix == 4)
    {
      puts("\nExécution de la tache correspondant au choix 4.");
      sleep(5);
    }
    else if (choix == 5)
    {
      puts("\nSortie du programme...\n");
      sleep(5);
      break;
    }
    else
    {
      puts("\nChoix incorrect, essayer de nouveau.");
      sleep(5);
    }
  }
  return 0;
}

int menu(void)
{
  int reponse;

  puts("\nEntrez 1 pour la teche A.");
  puts("\nEntrez 2 pour la teche B.");
  puts("\nEntrez 3 pour la teche C.");
  puts("\nEntrez 4 pour la teche D.");
  puts("\nEntrez 5 pour sortir du programme.");

  scanf("%d", &reponse);

  return reponse;
}