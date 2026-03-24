#include <stdio.h>

// Fonction récursive pour calculer 3^n
long puissanceTrois(int n)
{
  // Cas de base : tout nombre à la puissance 0 vaut 1
  if (n == 0)
  {
    return 1;
  }
  // Cas de base pour les puissances négatives (optionnel mais propre)
  if (n < 0)
  {
    printf("Erreur : Ce programme ne gere que les exposants positifs.\n");
    return 0;
  }

  // Cas récursif : 3^n = 3 * 3^(n-1)
  return 3 * puissanceTrois(n - 1);
}

int main()
{
  int exposant;
  long resultat;

  printf("Entrez l'exposant pour 3 (ex: 4 pour 3^4) : ");
  scanf("%d", &exposant);

  resultat = puissanceTrois(exposant);

  if (exposant >= 0)
  {
    printf("3 a la puissance %d est egal a %ld\n", exposant, resultat);
  }

  return 0;
}
