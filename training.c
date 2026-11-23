#include <nl_types.h>
#include <stdio.h>
#include <stdlib.h>
#include "exemple_catgets.h"

int main(void)
{
    nl_catd catalogue;
    char *chaine;
    if ((catalogue = catopen("msg_catgets", NL_CAT_LOCALE)) == (nl_catd)-1)
    {
        fprintf(stderr, "Unable to open catalog \n");
        exit(1);
    }
    chaine = catgets(catalogue, premier__Set, premier__chaine_1, "This is the first string in the first Set ");
    fprintf(stdout, "%s \n", chaine);
    chaine = catgets(catalogue, premier__Set, premier__chaine_2, "and here is the second string in the first Set ");
    fprintf(stdout, "%s \n", chaine);
    chaine = catgets(catalogue, second__Set, second__chaine_1, "Now let's have a look at the 1st string in 2nd set");
    fprintf(stdout, "%s \n", chaine);
    chaine = catgets(catalogue, second__Set, second__chaine_2, "and finally the second string in the 2nd set");
    fprintf(stdout, "%s \n", chaine);
    catclose(catalogue);
    return 0;
}