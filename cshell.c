#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "history.h"
#include "colors.h"

#define MAX_HISTORY 100

int main()
{
  Process history[MAX_HISTORY];
  int count = 0;

  while (1)
  {
    char input[256];
    print_green("cshell> ");
    fflush(stdout);

    if (fgets(input, sizeof(input), stdin) == NULL)
      break;

    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n')
      input[len - 1] = '\0';

    if (strcmp(input, "exit") == 0)
    {
      print_yellow("Exiting...\n");
      break;
    }

    printf("\033[0;33m[*] Executing: %s\033[0m \n", input);

    pid_t pid = fork();

    if (pid == 0)
    {
      char *args[] = {input, NULL};
      execvp(input, args);
      print_red("[X] exec failed\n");
      exit(1);
    }
    else if (pid > 0)
    {
      int status;
      waitpid(pid, &status, 0);

      if (count < MAX_HISTORY)
        add_to_history(history, &count, pid, input, WEXITSTATUS(status));
    }
    else
    {
      print_red("fork failed");
    }
  }

  write_history_to_file(history, count, "history.txt");
  return 0;
}
