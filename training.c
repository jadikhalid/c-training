#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include <stdint.h>

static void *thread_compteur(void *inutile);
static void *thread_signaux(void *inutile);
static void cleanup_mutex_unlock(void *arg);

static int compteur = 0;

static pthread_mutex_t mutex_compteur = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond_compteur = PTHREAD_COND_INITIALIZER;

static pthread_t thr_signaux;
static pthread_t thr_compteur;

int main(void)
{
    pthread_create(&thr_compteur, NULL, thread_compteur, NULL);
    pthread_create(&thr_signaux, NULL, thread_signaux, NULL);

    pthread_join(thr_compteur, NULL);
    pthread_join(thr_signaux, NULL);

    return 0;
}

// Wrapper pour adapter la signature de pthread_mutex_unlock à pthread_cleanup_push
static void cleanup_mutex_unlock(void *arg)
{
    pthread_mutex_unlock((pthread_mutex_t *)arg);
}

static void *thread_compteur(void *inutile)
{
    (void)inutile;
    sigset_t masque;

    // Bloque tous les signaux dans ce thread pour que seul thread_signaux les reçoive
    sigfillset(&masque);
    pthread_sigmask(SIG_BLOCK, &masque, NULL);

    while (1)
    {
        pthread_mutex_lock(&mutex_compteur);

        // Plus besoin de cast bancal de pointeur de fonction !
        pthread_cleanup_push(cleanup_mutex_unlock, &mutex_compteur);

        // Attente du signal de mise à jour du compteur
        pthread_cond_wait(&cond_compteur, &mutex_compteur);

        fprintf(stdout, "Compteur : %d\n", compteur);

        // Libère le mutex via le cleanup_pop (1 = exécute cleanup_mutex_unlock)
        pthread_cleanup_pop(1);

        if (compteur > 5)
        {
            break;
        }
    }

    // Annulation propre du thread gérant les signaux
    pthread_cancel(thr_signaux);

    return NULL;
}

static void *thread_signaux(void *inutile)
{
    (void)inutile;
    sigset_t masque;
    int numero;

    sigemptyset(&masque);
    sigaddset(&masque, SIGINT);  // Ctrl+C (+1)
    sigaddset(&masque, SIGQUIT); // Ctrl+\ (-1)

    // S'assure que ce thread intercepte ces signaux via sigwait
    pthread_sigmask(SIG_BLOCK, &masque, NULL);

    while (1)
    {
        // Attente synchrone d'un signal SIGINT ou SIGQUIT
        sigwait(&masque, &numero);

        pthread_mutex_lock(&mutex_compteur);
        switch (numero)
        {
        case SIGINT:
            compteur++;
            break;
        case SIGQUIT:
            compteur--;
            break;
        }
        pthread_cond_signal(&cond_compteur);
        pthread_mutex_unlock(&mutex_compteur);
    }

    return NULL;
}