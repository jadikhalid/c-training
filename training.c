#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include <time.h> // Nécessaire pour nanosleep

volatile int *entier;
sem_t *sem;

int main(void)
{
    char nom_fichier[] = "/tmp/ipc_shared_XXXXXX";
    int fichier;
    pid_t pid;

    // 1. Création d'un sémaphore POSIX nommé pour une synchronisation inter-processus parfaite
    sem_unlink("/ipc_sync_sem");
    sem = sem_open("/ipc_sync_sem", O_CREAT | O_EXCL, 0644, 0);
    if (sem == SEM_FAILED)
    {
        perror("sem_open");
        exit(1);
    }

    // 2. Création sécurisée du fichier temporaire via mkstemp
    fichier = mkstemp(nom_fichier);
    if (fichier < 0)
    {
        perror("mkstemp");
        sem_close(sem);
        sem_unlink("/ipc_sync_sem");
        exit(1);
    }

    // 3. Dimensionnement de la zone partagée
    if (ftruncate(fichier, sizeof(int)) < 0)
    {
        perror("ftruncate");
        close(fichier);
        sem_close(sem);
        sem_unlink("/ipc_sync_sem");
        exit(1);
    }

    // 4. Projection mémoire partagée
    entier = (int *)mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fichier, 0);
    if (entier == MAP_FAILED)
    {
        perror("mmap");
        close(fichier);
        sem_close(sem);
        sem_unlink("/ipc_sync_sem");
        exit(1);
    }

    close(fichier);
    unlink(nom_fichier);

    // 5. Création du processus fils
    if ((pid = fork()) < 0)
    {
        perror("fork");
        munmap((void *)entier, sizeof(int));
        sem_close(sem);
        sem_unlink("/ipc_sync_sem");
        exit(1);
    }

    if (pid == 0)
    {
        // ==========================
        // PROCESSUS FILS
        // ==========================
        while (1)
        {
            // Gestion propre de l'interruption potentielle par EINTR
            if (sem_wait(sem) < 0)
            {
                if (errno == EINTR)
                    continue;
                break;
            }

            // Lecture sécurisée et synchrone de la mémoire partagée
            char buffer[64];
            int len = snprintf(buffer, sizeof(buffer), "Fils : * entier = %d\n", *entier);
            if (len > 0)
            {
                // Cast explicite en size_t pour satisfaire -Wsign-conversion
                write(1, buffer, (size_t)len);
            }

            // Condition de sortie si le père indique la fin (ex: valeur 9)
            if (*entier >= 9)
                break;
        }

        munmap((void *)entier, sizeof(int));
        sem_close(sem);
        _exit(0);
    }
    else
    {
        // ==========================
        // PROCESSUS PÈRE
        // ==========================
        // Remplacement de l'obsolète usleep par nanosleep (50 millisecondes)
        struct timespec req = {0, 50000000L};

        for ((*entier) = 0; (*entier) < 10; (*entier)++)
        {
            fprintf(stdout, "Pere : * entier = %d\n", *entier);
            fflush(stdout);

            // Libère le sémaphore pour autoriser le fils à lire l'étape courante
            sem_post(sem);

            nanosleep(&req, NULL);
        }

        // Attente de la fin propre du fils (évite les processus zombies)
        wait(NULL);

        // Libération globale des ressources système
        munmap((void *)entier, sizeof(int));
        sem_close(sem);
        sem_unlink("/ipc_sync_sem");
    }

    return 0;
}