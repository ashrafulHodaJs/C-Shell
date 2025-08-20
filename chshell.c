#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include "colors.h"

typedef struct Process
{
  pid_t pid;
  char command[256];
  int status;
} Process;

int main()
{
  Process p1;
  Process *ptrp1 = malloc(sizeof(Process));

  while (1)
  {
    print_red("cshell> ");
    fflush(stdout);

    if (fgets(ptrp1->command, sizeof(ptrp1->command), stdin) == NULL)
    {
      break;
    }
    // fgets includes \n character so we need to strip that down
    int cmdlen = strlen(ptrp1->command);
    if (cmdlen > 0 && ptrp1->command[cmdlen - 1] == '\n')
    {
      ptrp1->command[cmdlen - 1] = '\0';
    }
    // exit program
    if (strcmp(ptrp1->command, "exit") == 0)
    {
      print_yellow("Exiting...\n");
      break;
    };

    printf("[*] Executing: %s\n", ptrp1->command);
    // Forking and execing
    pid_t pid = fork();

    if (pid == 0)
    {
      // child process
      char *args[] = {ptrp1->command, NULL};
      execvp(ptrp1->command, args);
      print_red("[X] execvp failed");
      exit(1);
    }
    else if (pid > 0)
    {
      // parent
      ptrp1->pid = pid;
      waitpid(pid, &ptrp1->status, 0);
      printf("\033[0;33m[+] Child %d exited with status %d\n\033[0m", ptrp1->pid, WEXITSTATUS(ptrp1->status));
    }
    else
    {
      perror("fork");
    }
  }
  free(ptrp1);

  return 0;
}
