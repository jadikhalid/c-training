#include <stdio.h>

int main(int argc, char *argv[])
{
  printf("========================================\n");
  printf("   Test du Compilateur GCC sur Linux    \n");
  printf("========================================\n");

  // Test de l'affichage simple
  printf("[OK] Le binaire a ete genere avec succes.\n");

  // Test des arguments (pour vérifier la liaison future)
  if (argc > 1)
  {
    printf("[INFO] Argument detecte : %s\n", argv[1]);
  }
  else
  {
    printf("[INFO] Aucun argument passe au programme.\n");
  }

  printf("========================================\n");
  return 0;
}