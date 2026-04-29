#include <stdio.h>

int main()
{
  unsigned int nombre = 255;
  unsigned int couleur = 0x3A7F12;

  printf("--- Comparaison minuscules / majuscules ---\n");
  printf("En minuscules (%%x) : %x\n", nombre); // Affiche "ff"
  printf("En majuscules (%%X) : %X\n", nombre); // Affiche "FF"

  printf("\n--- Exemple avec un nombre plus grand ---\n");
  printf("Code couleur (%%x) : %x\n", couleur); // Affiche "3a7f12"
  printf("Code couleur (%%X) : %X\n", couleur); // Affiche "3A7F12"

  // Astuce : Utiliser le flag '#' pour ajouter le préfixe '0x' automatiquement
  printf("\n--- Avec le préfixe automatique ---\n");
  printf("Format pro (%%#x) : %#x\n", couleur); // Affiche "0x3a7f12"
  printf("Format pro (%%#X) : %#X\n", couleur); // Affiche "0X3A7F12"

  return 0;
}