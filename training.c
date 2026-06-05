/* Utilisation des macros de test de caracteres pour
   réaliser  une fonction lisant un entier au clavier  */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

int get_in(void);

int main()
{
  int x;
  x = get_in();
  printf("Vous avez tape : %d.\n", x);

  return 0;
}

int get_in(void)
{
  int ch, i, sign = 1;
  bool temoin = true;
  while (temoin)
  {
    /* Ignorer les espaces en tete */
    puts("Tapez un chiffre");
    while (isspace(ch = getchar()))
      ;
    /* Si le premier caractere n'est pas numérique
    le recracher et renvoyer 0 */
    if (ch != '-' && ch != '+' && !isdigit(ch) && ch != EOF)
    {
      puts("Entree invalide");
      /* VIDER LE STDIN : on consomme tout jusqu'au '\n' */
      int c;
      while ((c = getchar()) != '\n' && c != EOF)
        ;
      continue;
    }

    /* Si le premier caractere est un signe -,
    placer le signe du résultat */
    if (ch == '-')
      sign = -1;

    /* Si le premier caractere est un signe + ou
    un signe -, lire le aractere suivant */
    if (ch == '+' || ch == '-')
      ch = getchar();

    /* Lire les caractere jusqu a tomber sur un
    non chiffre. Effectuer la conversion en
    multipliant chacun des chiffres lus par
    la bonne puissance de 10 */
    for (i = 0; isdigit(ch); ch = getchar())
      i = 10 * i + (ch - '0');

    /* Corriger éventuellement le signe */
    i *= sign;

    /* Si on n a pas rencontré le EOF, on recrache le caractere
    non numerique. */
    if (ch != EOF)
      ungetc(ch, stdin);

    temoin = false;
  }
  /* Renvoyer la valeur finale*/
  return i;
}