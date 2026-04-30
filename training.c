/*
 * Utilisation de printf()
 */

#include <stdio.h>
#include <stdlib.h>

char *m1 = "Binaire";
char *m2 = "Decimal";
char *m3 = "Octal";
char *m4 = "Hexadecimal";

int main()
{
  float d1 = 10000.123;
  int n, c;

  puts("Affichage d'un nombre avec plusieurs largeurs de champ");
  printf("%5f\n", d1);
  printf("%10f\n", d1);
  printf("%15f\n", d1);
  printf("%20f\n", d1);
  printf("%25f\n", d1);

  puts("\n Appuyez sur entrée pour continuer ...");

  while ((c = getchar()) != '\n' && c != EOF)
    ;

  getchar();

  puts("\nOn utilise * pour la largeur de champ");
  puts("d'une variable de la liste ds arguments.\n");

  for (n = 5; n <= 25; n += 5)
    printf("%*f\n", n, d1);

  puts("\n Appuyez sur Entrée pour continuer...");

  while ((c = getchar()) != '\n' && c != EOF)
    ;

  getchar();

  puts("\n On complète avec des 0");

  printf("%05f\n", d1);
  printf("%010f\n", d1);
  printf("%015f\n", d1);
  printf("%020f\n", d1);
  printf("%025f\n", d1);

  puts("\n Appuyez sur Entrée pour continuer...");

  while ((c = getchar()) != '\n' && c != EOF)
    ;

  getchar();

  puts("\nAffichage en octal, decimal et hexadecimal.");

  printf("%-15s%-15s%-15s", m2, m3, m4);

  for (n = 1; n < 20; n++)
    printf("\n%-15d%-#15o%-#15X", n, n, n);

  puts("\n\nOn utilise la commande de conversion %n pour compter");
  puts("les caracteres.\n");
  printf("%s %s %s %s %n", m1, m2, m3, m4, &n);

  printf("\n\nLe dernier printf() a affiché %d caractères.\n", n);

  return 0;
}
