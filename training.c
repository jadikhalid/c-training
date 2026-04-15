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
    /* code */
  }
}