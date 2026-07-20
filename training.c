#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <errno.h>

static int temporisation_ecoulee;

void gestionnaie_sigalrm(int inutile)
{
  (void)inutile;
  temporisation_ecoulee = 1;
}

int sommeil_precis(long nb_secondes, long nb_micosecondes)
{
  struct sigaction action;
  struct sigaction ancienne_action;
  sigset_t masque_sigalrm;
  sigset_t ancien_masque;

  int sigalrm_dans_ancien_mask = 0;

  struct itimerval ancien_timer;
  struct itimerval nouveau_timer;

  int retour = 0;

  /* Préparation du timer */
  timeclear(&(nouveau_timer.it_interval));
  nouveau_timer.it_value.tv_sec = nb_secondes;
  nouveau_timer.it_value.tv_usec = nb_micosecondes;

  /* Installation du gestionnaire d'alarme */
  action.sa_handler = gestionnaie_sigalrm;
  sigemptyset(&(action.sa_mask));
  action.sa_flags = SA_RESTART;
  if (sigprocmask(SIGALRM, &action, &ancienne_action) != 0)
    return (-1);
}