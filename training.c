#define _XOPEN_SOURCE 500
#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <stdlib.h>

void recherche_variable(char *nom);

int main(void)
{
  fprintf(stdout, "\n--- test de putenv() --- \n");
  recherche_variable("ESSAI");
  fprintf(stdout, "putenv(\"ESSAI=UN\");\n");
  putenv("ESSAI=UN");
  recherche_variable("ESSAI");

  fprintf(stdout, "putenv (\"ESSAI=\");\n");
  putenv("ESSAI=");
  recherche_variable("ESSAI");
  fprintf(stdout, "putenv (\"ESSAI\"); équivaut à unsetenv( )\n");
  putenv("ESSAI");
  recherche_variable("ESSAI");

  fprintf(stdout, "\n--- test de setenv( ) --- \n");
  recherche_variable("ESSAI");
  fprintf(stdout, "setenv (\"ESSAI\", \"DEUX\", 1);\n");
  setenv("ESSAI", "DEUX", 1);
  recherche_variable("ESSAI");

  fprintf(stdout, "setenv (\"ESSAI\", \"TROIS\", 1);\n");
  setenv("ESSAI", "TROIS", 1);
  recherche_variable("ESSAI");

  fprintf(stdout, "setenv (\"ESSAI\", \"QUATRE\", 0);"
                  " écrasement de valeur non autorisé\n");
  setenv("ESSAI", "QUATRE", 0);
  recherche_variable("ESSAI");

  fprintf(stdout, "\n-- test de unsetenv( ) -- \n");
  recherche_variable("ESSAI");
  fprintf(stdout, "unsetenv (\"ESSAI\");\n");
  unsetenv("ESSAI");
  recherche_variable("ESSAI");

  return EXIT_SUCCESS;
}

void recherche_variable(char *nom)
{
  char *valeur;
  fprintf(stdout, " variable %s ", nom);
  valeur = getenv(nom);
  if (valeur == NULL)
    fprintf(stderr, "Inexistante.\n");
  else
    fprintf(stdout, " = %s\n", valeur);
}