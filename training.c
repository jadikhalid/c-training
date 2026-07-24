#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *alloc_printf(const char *format, ...);

int main(void)
{
  char *buffer;
  char *seizecars = "0123456789ABCDEF";
  buffer = alloc_printf(" %s %s", seizecars, seizecars);
  if (buffer != NULL)
  {
    fprintf(stdout, "Chaine de %d caracteres \n %s \n", (int)strlen(buffer), buffer);
    free(buffer);
  }
  buffer = alloc_printf(" %s %s %s %s", seizecars, seizecars, seizecars, seizecars);
  if (buffer != NULL)
  {
    fprintf(stdout, "Chine de %d caracteres \n %s \n", (int)strlen(buffer), buffer);
    free(buffer);
  }

  return 0;
}

char *alloc_printf(const char *format, ...)
{
  va_list arguments;
  char *retour = NULL;
  int taille = 64;
  int nb_ecrits;

  va_start(arguments, format);
  while (1)
  {
    retour = realloc(retour, (size_t)taille);
    if (retour == NULL)
    {
      va_end(arguments);
      return NULL;
    }

    // On crée une copie de la va_list pour ce tour de boucle
    va_list args_copie;
    va_copy(args_copie, arguments);

    nb_ecrits = vsnprintf(retour, (size_t)taille, format, args_copie);

    va_end(args_copie); // On nettoie la copie

    if ((nb_ecrits >= 0) && (nb_ecrits < taille))
      break;

    taille = taille + 64;
  }
  va_end(arguments);
  return (retour);
}