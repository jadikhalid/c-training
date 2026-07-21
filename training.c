#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <errno.h>

unsigned long int mode_utilisateur;
unsigned long int mode_utilisateur_et_noyau;

void gestionnaire_signaux(int numero);
void fin_du_suivi(void);
void action_a_mesurer(void);

int main(void)
{
  struct sigaction action;
  struct itimerval timer;

  /* Preparation du timer */
  timer.it_value.tv_sec = 0;
  timer.it_value.tv_usec = 10000;
  timer.it_interval.tv_sec = 0;
  timer.it_interval.tv_usec = 10000;

  /* Installation du gestionnaire de signaux */
  action.sa_handler = gestionnaire_signaux;
  sigemptyset(&(action.sa_mask));
  action.sa_flags = SA_RESTART;
  if ((sigaction(SIGVTALRM, &action, NULL) != 0) || (sigaction(SIGPROF, &action, NULL) != 0))
  {
    fprintf(stderr, "Erreur á l'appel de la fonction sigaction()");
    return (-1);
  }

  /* Déclenchement des nouveaux timers */
  if ((setitimer(ITIMER_VIRTUAL, &timer, NULL)) != 0 || (setitimer(ITIMER_PROF, &timer, NULL)) != 0)
  {
    fprintf(stderr, "Erreur á l'appel de setitmer()");
    return -1;
  }
}