/* Acces aleatoire avec fseek() */

#include <stdio.h>
#include <stdlib.h>

#define MAX 50

int main()
{
  FILE *fp;
  int data, count, array[MAX];
  long offset;

  /* Initialiser le tableau */
  for (count = 0; count < MAX; count++)
    array[count] = count * 2;

  /* Ouvrir un fichier binaire en ecriture */
  if ((fp = fopen("random.dat", "wb")) == NULL)
  {
    fprintf(stderr, "\nErreur a l ouverture du fichier.");
    return 1;
  }

  /* Ecrire le tableau dans le fichier puis le refermer */
  if ((fwrite(array, sizeof(*array), MAX, fp)) != MAX)
  {
    fprintf(stderr, "\nErreur a l ecriture dans le fichier.");
    return 1;
  }

  fclose(fp);

  /* Ouvrir le fichier en lecture */
  if ((fp = fopen("random.dat", "rb")) == NULL)
  {
    fprintf(stderr, "\nErreur a l ouverture du fichier");
    return 1;
  }

  /* Demander a l utilisateur quel element il veut lire
  Lire l element et l afficher . Arreter lorsqu il
  repond -1 */

  while (1)
  {
    printf("\nIndiquez l element a lire, 0-%d, \
      -1 pour arreter : ",
           MAX - 1);
    scanf("%ld", &offset);
    if (offset < 0)
      break;
    else if (offset > MAX - 1)
      continue;
    /* Deplacer l indicateur de position sur l element specifie */
    if (fseek(fp, (offset * sizeof(int)), SEEK_SET))
    {
      fprintf(stderr, "\nErreur avec fseek().");
      return 1;
    }
    /* Lire un unique entirt */
    fread(&data, sizeof(data), 1, fp);

    printf("\nL element %ld a la veleur %d.", offset, data);
  }

  fclose(fp);

  return 0;
}