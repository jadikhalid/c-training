#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>

int main(void)
{
    time_t t;
    t = time(NULL);
    fprintf(stdout, "%s", ctime(&t));
    return 0;
}