#include <stdio.h>
#include <ctype.h>

/**
 * Recherche la premiere occurrence de la chaine 'aiguille' dans 'meule_de_foin'
 * sans distinction entre majuscules et minuscules.
 *
 * @param meule_de_foin La chaine dans laquelle on cherche.
 * @param aiguille      La sous-chaine a rechercher.
 * @return Un pointeur sur le debut de la sous-chaine trouvee, ou NULL.
 */
char *mon_strcasestr(const char *meule_de_foin, const char *aiguille)
{
  // Regle standard de strstr : si l'aiguille est vide, on renvoie le debut de la meule
  if (*aiguille == '\0')
  {
    return (char *)meule_de_foin;
  }

  // Parcourir la meule de foin caractere par caractere
  for (int i = 0; meule_de_foin[i] != '\0'; i++)
  {

    // Si le premier caractere correspond (en ignorant la casse)
    if (tolower((unsigned char)meule_de_foin[i]) == tolower((unsigned char)aiguille[0]))
    {

      int j = 0;
      // On verifie si toute la suite de l'aiguille correspond
      while (aiguille[j] != '\0' && meule_de_foin[i + j] != '\0' &&
             tolower((unsigned char)meule_de_foin[i + j]) == tolower((unsigned char)aiguille[j]))
      {
        j++;
      }

      // Si on a parcouru toute l'aiguille avec succes, on a trouve !
      if (aiguille[j] == '\0')
      {
        return (char *)&meule_de_foin[i];
      }
    }
  }

  return NULL; // Aucune occurrence trouvee
}

int main(void)
{
  const char *texte = "Developper en Langage C est Genial";
  const char *recherche = "lAnGaGe";

  char *resultat = mon_strcasestr(texte, recherche);

  if (resultat != NULL)
  {
    printf("Occurrence trouvee ! Reste de la chaine : \"%s\"\n", resultat);
  }
  else
  {
    printf("Sous-chaine non trouvee.\n");
  }

  return 0;
}