#include <stdio.h>
#include <stdlib.h>

// Fonction utilitaire pour vider le tampon d'entrée standard (stdin)
void viderTampon()
{
  int c;
  // Lit les caractères un par un jusqu'à trouver '\n' (Entrée) ou la fin de fichier (EOF)
  while ((c = getchar()) != '\n' && c != EOF)
  {
    // On ne fait rien, on jette juste le caractère lu
  }
}

int main()
{
  int choix;

  do
  {
    // 1. Afficher le menu à chaque tour
    printf("\n--- MENU DE COMMANDES SYSTEME ---\n");
    printf("1. Lister les fichiers (dir / ls)\n");
    printf("2. Creer un fichier texte (echo > ...)\n");
    printf("3. Afficher la date et l'heure\n");
    printf("4. Afficher les infos systeme\n");
    printf("5. Quitter le programme\n");
    printf("Votre choix : ");

    // 2. Lire le choix de l'utilisateur
    // On tente de lire un entier
    if (scanf("%d", &choix) != 1)
    {
      // SI CA ECHOUE (l'utilisateur a tapé du texte, 'a', 'bonjour'...)
      printf("\n--- Erreur de saisie : Veuillez entrer un NOMBRE entier. ---\n");

      // CORRECTION ICI : On vide le tampon pour enlever les caractères invalides
      viderTampon();

      // On affecte une valeur qui forcera le cas 'default' du switch
      choix = 0;
    }
    else
    {
      // SI LA LECTURE DU NOMBRE A REUSSI
      // Il reste souvent le '\n' (Entrée) dans le tampon.
      // C'est une bonne habitude de vider le tampon même après un succès
      // pour éviter des problèmes lors de futures lectures de caractères/chaînes.
      viderTampon();
    }

    // 3. Agir en fonction du choix
    // printf("\nAction choisie : %d\n", choix); // Optionnel, pour débugger

    switch (choix)
    {
    case 1:
      printf("\n--- Execution de 'lister fichiers' ---\n");
#ifdef _WIN32
      system("dir");
#else
      system("ls");
#endif
      break;
    case 2:
      printf("\n--- Creation de salut.txt ---\n");
      system("echo Bonjour tout le monde > salut.txt");
      break;
    case 3:
      printf("\n--- Affichage date/heure ---\n");
#ifdef _WIN32
      system("time /t & date /t");
#else
      system("date");
#endif
      break;
    case 4:
      printf("\n--- Infos Systeme ---\n");
#ifdef _WIN32
      system("systeminfo");
#else
      system("uname -a");
#endif
      break;
    case 5:
      printf("\nFin du programme. Au revoir !\n");
      break;
    default:
      // Ce cas est atteint si choix == 0 (erreur de saisie)
      // ou si l'utilisateur a tapé un nombre hors de 1-5 (ex: 8)
      if (choix != 0)
      {
        printf("\n--- Choix invalide : Le nombre doit etre entre 1 et 5. ---\n");
      }
      break;
    }

  } while (choix != 5);

  return 0;
}