/*
 * Exemple de redirection de stdin et stdout
 */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "utilitaires.h"

int main()
{
  SetConsoleOutputCP(65001);
  SetConsoleCP(65001);
  char buf[80];
  lire_clavier(buf, sizeof(buf));
  printf("L'entrée était : %s\n", buf);

  return 0;
}