#define _GNU_SOURCE

#include <math.h>
#include <stdio.h>

int main(void)
{
    double d;
    d = cos(M_PI / 4) * 2.0;
    d = d * d - 2.0;
    fprintf(stdout, "(2*cos(PI/4))2-2 = %e \n", d);
    return 0;
}