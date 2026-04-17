/*
 * Programme coder.c
 * Syntaxe : coder [monfichier] [action]
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int encode_character(int ch, int val);
int decode_character(int ch, int val);

int main(int argc, char *argv[])
{
  FILE *fh;
  int rv = 1;
  int ch = 0;
  unsigned int crt = 0;
  int val = 5;
  char buffer[257];

  if (argc != 3)
  {
    printf("\nErreur: nombre de parametres incorecte ...");
    printf("\n\nSyntaxe:\n %s nomfichier action", argv[0]);
    printf("\n\n Ou:");
    printf("\n nomfichier = nom du fichier a coder");
    printf("\nou a decoder");
    printf("\n action = D pour decoder ou C pour code \n\n");
    rv = -1;
  }
  else if ((argv[2][0] == 'D') || (argv[2][0] == 'd'))
  {
    fh = fopen(argv[1], "r");
    if (fh == 0)
    {
      printf("\n\nErreur d ouverture du fichier...");
      rv = -2;
    }
    else
    {
      ch = getc(fh);
      while (!feof(fh))
      {
        ch = decode_character(ch, val);
        putchar(ch);
        ch = getc(fh);
      }
      fclose(fh);
      printf("\n\nFichier deocdé et affiché.\n");
    }
  }
  else
  {
    fh = fopen(argv[1], "w");
    if (fh == 0)
    {
      printf("\n\nErreur pendant la creation du fichier...");
      rv = -3;
    }
    else
    {
      printf("\n\nEntrez le texte a coder...");
      printf("\nEntrz une ligne vide pour terminer.\n\n");
      while (fgets(buffer, sizeof(buffer), stdin))
      {
        if ((buffer[0] == 0) || (buffer[0] == '\n'))
          break;
        for (crt = 0; crt < strlen(buffer); crt++)
        {
          ch = encode_character(buffer[crt], val);
          ch = fputc(ch, fh);
        }
      }
      printf("\n\nMessage codé et enregistré.\n");
      fclose(fh);
    }
  }
  exit((rv == 1) ? EXIT_SUCCESS : EXIT_FAILURE);
}

int encode_character(int ch, int val)
{
  ch = ch + val;
  return ch;
}

int decode_character(int ch, int val)
{
  ch = ch - val;
  return ch;
}
