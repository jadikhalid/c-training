#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
  int pipefd[2];
  char *user = getenv("USER");

  if (user == NULL)
    return 1;

  // 1. Création d'un pipe pour communiquer avec le futur processus "mail"
  if (pipe(pipefd) == -1)
  {
    perror("pipe");
    return 1;
  }

  pid_t pid = fork();

  if (pid == -1)
  {
    perror("fork");
    return 1;
  }

  if (pid == 0)
  {
    // --- PROCESSUS FILS : va devenir "mail" ---
    close(pipefd[1]);              // Ferme le côté écriture (non utilisé)
    dup2(pipefd[0], STDIN_FILENO); // Redirige l'entrée standard vers le pipe
    close(pipefd[0]);

    // Exécution directe de "mail" sans passer par un shell
    // execlp cherche "mail" dans le PATH
    execlp("mail", "mail", user, NULL);

    // Si execlp échoue
    perror("execlp");
    exit(1);
  }
  else
  {
    // --- PROCESSUS PÈRE : envoie le message ---
    close(pipefd[0]); // Ferme le côté lecture (non utilisé)

    FILE *message = fdopen(pipefd[1], "w");
    if (message != NULL)
    {
      fprintf(message, "Ceci est un message sécurisé\n");
      fprintf(message, "écrit par moi-même sans shell\n");
      fclose(message); // Ferme et envoie le signal EOF au processus mail
    }

    wait(NULL); // Attend la fin du fils
  }

  return 0;
}