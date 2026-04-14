#include <stdio.h>

void exemple_de_fonction(void)
{
  int ctr1;
  for (ctr1 = 0; ctr1 < 25; ctr1++)
    printf("*");

  puts("\nCela est un exemple de fonction");

  // Bloc interne isolé
  {
    char star = '*'; // Utilisation de l'apostrophe droite
    puts("il y a un problème");
    for (int ctr2 = 0; ctr2 < 25; ctr2++)
    {
      printf("%c", star);
    }
    printf("\n");
  }
}

int main()
{
  exemple_de_fonction();
  return 0;
}