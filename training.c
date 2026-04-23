#include <stdio.h>
#include <stdlib.h>

int main()
{
  double num1, num2, resultat;
  char operateur;

  printf("--- Calculatrice C v1.0 ---\n");
  printf("Entrez l'operation (ex: 5 + 3) : ");

  // Lecture : le premier nombre, l'operateur et le deuxieme nombre
  // L'espace avant %c est crucial pour ignorer les espaces blancs
  if (scanf("%lf %c %lf", &num1, &operateur, &num2) != 3)
  {
    printf("Erreur : Format de saisie invalide.\n");
    return 1;
  }

  switch (operateur)
  {
  case '+':
    resultat = num1 + num2;
    printf("Resultat : %.2f\n", resultat);
    break;

  case '-':
    resultat = num1 - num2;
    printf("Resultat : %.2f\n", resultat);
    break;

  case '*':
    resultat = num1 * num2;
    printf("Resultat : %.2f\n", resultat);
    break;

  case '/':
    // Verification de la division par zero
    if (num2 != 0)
    {
      resultat = num1 / num2;
      printf("Resultat : %.2f\n", resultat);
    }
    else
    {
      printf("Erreur : Division par zero impossible !\n");
    }
    break;

  default:
    printf("Erreur : Operateur '%c' non reconnu.\n", operateur);
    break;
  }

  return 0;
}