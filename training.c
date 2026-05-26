#include <stdio.h>
#include <ctype.h>

int main()
{
  int c;
  FILE *fp1, *fp2;
  if ((fp1 = fopen("resultat.txt", "rb")) == NULL)
  {
    fprintf(stderr, "Erreur los de l'ouverture du fichier result.txt");
    return 1;
  }
  if ((fp2 = fopen("copieresultat.txt", "wb")) == NULL)
  {
    fprintf(stderr, "Erreur los de l'ouverture du fichier  copieresult.txt");
    return 1;
  }
  while ((c = fgetc(fp1)) != EOF)
  {
    fputc(toupper(c), fp2);
  }

  return 0;
}