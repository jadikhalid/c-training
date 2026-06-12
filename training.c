#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Fonction utilitaire pour vider le tampon de saisie et éviter les boucles infinies
void vider_tampon(void)
{
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

// Fonction de saisie sécurisée pour les nombres réels (double)
double saisir_double(const char *message)
{
  double valeur;
  int statut;
  while (1)
  {
    printf("%s", message);
    statut = scanf("%lf", &valeur);
    if (statut == 1)
    {
      vider_tampon();
      return valeur;
    }
    printf("⚠️ Saisie invalide. Veuillez entrer un nombre correct.\n");
    vider_tampon();
  }
}

// Fonction de saisie sécurisée pour les entiers (durée)
int saisir_entier(const char *message)
{
  int valeur;
  int statut;
  while (1)
  {
    printf("%s", message);
    statut = scanf("%d", &valeur);
    if (statut == 1 && valeur > 0)
    {
      vider_tampon();
      return valeur;
    }
    printf("⚠️ Saisie invalide. La duree doit etre un entier superieur a 0.\n");
    vider_tampon();
  }
}

int main(void)
{
  printf("==================================================\n");
  printf("       SIMULATEUR D'EMPRUNT OPTIMISÉ EN C        \n");
  printf("==================================================\n\n");

  // 1. Saisie des données avec contrôle de robustesse
  double principal = saisir_double("Entrez le montant de l'emprunt (DH) : ");
  if (principal <= 0)
  {
    printf("❌ Le montant de l'emprunt doit etre strictement positif.\n");
    return EXIT_FAILURE;
  }

  double taux_annuel = saisir_double("Entrez le taux d'interet annuel (%%, ex: 12 pour 12%%) : ");
  int mois = saisir_entier("Entrez la duree du remboursement (en mois) : ");

  // 2. Pré-calculs et gestion des cas limites (Taux 0 et Négatif)
  double taux_mensuel = (taux_annuel / 100.0) / 12.0;
  double mensualite = 0.0;

  if (fabs(taux_mensuel) < 1e-9)
  {
    // Cas où le taux est strictement 0% (Évite la division par zéro)
    mensualite = principal / mois;
  }
  else
  {
    // Formule standard (Fonctionne aussi pour un taux négatif sans planter)
    mensualite = (principal * taux_mensuel) / (1.0 - pow(1.0 + taux_mensuel, -mois));
  }

  // 3. Affichage du résumé du crédit
  printf("\n==================================================\n");
  printf("               RESUME DU CREDIT                   \n");
  printf("==================================================\n");
  printf("Capital emprunte : %15.2f DH\n", principal);
  printf("Taux Annuel      : %15.2f %%\n", taux_annuel);
  printf("Durée            : %15d mois\n", mois);
  printf("Mensualité fixe  : %15.2f DH\n", mensualite);
  printf("==================================================\n\n");

  // 4. Génération et affichage du tableau d'amortissement
  printf("+------+-------------------+-------------------+-------------------+-------------------+\n");
  printf("| Mois |  Solde Initial    |  Interets Payes   | Capital Rembourse |  Solde Restant    |\n");
  printf("+------+-------------------+-------------------+-------------------+-------------------+\n");

  double solde_courant = principal;
  double cumul_interets = 0.0;

  for (int i = 1; i <= mois; i++)
  {
    double interet_mois = solde_courant * taux_mensuel;
    double capital_rembourse_mois = mensualite - interet_mois;

    // Ajustement de précision pour le tout dernier mois (évite les résidus de calcul à 0.01 près)
    if (i == mois)
    {
      capital_rembourse_mois = solde_courant;
      mensualite = capital_rembourse_mois + interet_mois;
    }

    double solde_restant = solde_courant - capital_rembourse_mois;
    cumul_interets += interet_mois;

    // Affichage parfaitement aligné grâce aux spécificateurs de format %14.2f
    printf("| %4d | %14.2f DH | %14.2f DH | %14.2f DH | %14.2f DH |\n",
           i, solde_courant, interet_mois, capital_rembourse_mois, fabs(solde_restant));

    solde_courant = solde_restant;
  }

  printf("+------+-------------------+-------------------+-------------------+-------------------+\n");
  printf("| TOTAL|                   | %14.2f DH | %14.2f DH |                   |\n",
         cumul_interets, principal);
  printf("+------+-------------------+-------------------+-------------------+-------------------+\n");
  printf("\n Coût total du credit (Capital + Interets) : %.2f DH\n", principal + cumul_interets);

  printf("\nAppuyez sur Entree pour quitter l'application...");
  getchar();

  return EXIT_SUCCESS;
}