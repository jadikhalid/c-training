/* Fonctions de temps */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// --- BLOC DE COMPATIBILITÉ WINDOWS ---
#ifdef _WIN32
// Définition de la structure tms manquante sous Windows
struct tms
{
  clock_t tms_utime;  // Temps utilisateur
  clock_t tms_stime;  // Temps système
  clock_t tms_cutime; // Temps enfants
  clock_t tms_cstime;
};

// On crée une fausse fonction pour remplacer celle de Linux
// On utilise 'static inline' pour éviter les conflits de liaison (linkage)
static inline clock_t times(struct tms *buf)
{
  if (buf != NULL)
  {
    buf->tms_utime = clock(); // On met le temps global dans le compartiment "User"
    buf->tms_stime = 0;
    buf->tms_cutime = 0;
    buf->tms_cstime = 0;
  }
  return clock();
}

// On définit une constante de remplacement pour simuler Linux
#define WINDOWS_TICKS_PER_SEC CLOCKS_PER_SEC

#else
// Si le code tourne sous Linux/POSIX
#include <unistd.h>
#include <sys/times.h>
#define WINDOWS_TICKS_PER_SEC sysconf(_SC_CLK_TCK)
#endif
// -------------------------------------

int main(void)
{
  time_t start, finish, now;
  struct tm *ptr;
  char *c, buf1[80];
  double duration;
  clock_t top_start, top_finish;
  struct tms buf;

  /* Heure de début de l'execution */
  start = time(0);
  top_start = times(&buf);

  /* Appel de ctime() pour enregistrer l instant de debut du programme */
  time(&now);

  /* Convertir la valeur time en une structure de type tm. */
  ptr = localtime(&now);

  /* Créer et afficher une chaîne de caractères contenant l’heure actuelle. */
  c = asctime(ptr);
  puts(c);
  getc(stdin);

  /* Utiliser maintenant la fonction strftime() pour créer
     plusieurs versions formatées du temps (date/heure) */
  // Correction des retours à la ligne dans la chaîne de caractères
  strftime(buf1, sizeof(buf1), "Nous sommes dans la semaine %U de l'annee %Y", ptr);
  puts(buf1);
  getc(stdin);

  strftime(buf1, sizeof(buf1), "Aujourd'hui, nous sommes %A, %x", ptr);
  puts(buf1);
  getc(stdin);

  strftime(buf1, sizeof(buf1), "Il est %H heures et %M minutes.", ptr);
  puts(buf1);
  getc(stdin);

  /* Prenons l’heure courante pour obtenir la durée d’exécution du programme. */
  finish = time(0);
  top_finish = times(&buf);
  duration = difftime(finish, start);

  printf("\nDuree d'execution du programme en utilisant time() = %.f secondes.", duration);

  /* Affichons la même durée, mais calculée avec times(). */
  // Utilisation de WINDOWS_TICKS_PER_SEC qui s'adapte à Windows ou Linux
  printf("\nDuree d'execution du programme en utilisant clock() = %ld centiemes de seconde.\n",
         100 * (top_finish - top_start) / WINDOWS_TICKS_PER_SEC);

  return EXIT_SUCCESS;
}