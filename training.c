#include <stdio.h>

void afficher_binaire(unsigned int nombre)
{
  // Un unsigned int fait généralement 4 octets, soit 32 bits
  int taille_bits = sizeof(nombre) * 8;
  int bit_trouve = 0; // Pour ignorer les zéros inutiles au début (optionnel)

  printf("Valeur binaire de %u : ", nombre);

  // Si le nombre est strictement 0, on affiche juste 0
  if (nombre == 0)
  {
    printf("0");
  }
  else
  {
    // On parcourt les bits du plus fort (gauche) au plus faible (droite)
    for (int i = taille_bits - 1; i >= 0; i--)
    {
      // On décale le bit 'i' vers la position 0, et on applique un masque avec 1
      int bit = (nombre >> i) & 1;

      if (bit == 1)
      {
        bit_trouve = 1; // On a trouvé le premier bit significatif
      }

      // On commence à afficher seulement après le premier bit à 1
      if (bit_trouve)
      {
        printf("%d", bit);
      }
    }
  }
  printf("\n");
}

int main()
{
  unsigned int valeur = 258;

  afficher_binaire(valeur);

  return 0;
}