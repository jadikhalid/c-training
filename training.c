
#include <stdio.h>
#include <stdlib.h>

#define NB_ELEMENTS 10

int comparer_pointeurs(const void *a, const void *b)
{
  // a et b sont des pointeurs vers les cases de tab_ptr, donc des double**
  double *ptr_a = *(double **)a;
  double *ptr_b = *(double **)b;

  if (*ptr_a < *ptr_b)
    return -1;
  if (*ptr_a > *ptr_b)
    return 1;
  return 0;
}

int main()
{
  double *tab_ptr[NB_ELEMENTS];
  double valeurs[NB_ELEMENTS];

  printf("Veuillez saisir %d nombres réels séparés par entrée:\n", NB_ELEMENTS);

  for (int i = 0; i < NB_ELEMENTS; i++)
  {
    printf("Valeur %d : ", i + 1);

    if (scanf("%lf", &valeurs[i]) != 1)
    {
      fprintf(stderr, "Erreur de saisie. Fin de programme.\n");
      return 1;
    }
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
      ;

    tab_ptr[i] = &valeurs[i];
  }

  // TRI ****************************** :
  qsort(tab_ptr, NB_ELEMENTS, sizeof(double *), comparer_pointeurs);

  // AFFICHAGE *********************** :
  printf("\n--- Tableau original 'valeurs' (inchangé) ---\n");
  for (int i = 0; i < NB_ELEMENTS; i++)
  {
    printf("valeurs[%d] = %.2f\n", i, valeurs[i]);
  }

  printf("\n--- Tableau 'tab_ptr' (trié du plus petit au plus grand) ---\n");
  for (int i = 0; i < NB_ELEMENTS; i++)
  {
    printf("Pointeur %d pointe vers %.2f\n", i, *tab_ptr[i]);
  }

  return 0;
}
