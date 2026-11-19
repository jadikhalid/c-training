#include <stdio.h>
#include <utmp.h>
#include <time.h>

void affiche_utmp(struct utmp *utmp)
{
    struct tm *tm;
    char heure[80];
    tm = localtime(&(utmp->ut_tv.tv_sec));
    strftime(heure, 80, "%X %X", tm);
    switch (utmp->ut_type)
    {
    case EMPTY:
        break;
    case RUN_LVL:
        printf("%s ", heure);
        printf("Run-level\n");
        break;
    case BOOT_TIME:
        printf("%s ", heure);
        printf("Boot \n");
        break;
    case OLD_TIME:
        printf("%s ", heure);
        printf("Old Time \n");
        break;
    }
}