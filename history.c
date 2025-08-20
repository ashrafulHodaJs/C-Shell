#include "history.h"
#include <stdio.h>
#include <string.h>

void add_to_history(Process history[], int *count, pid_t pid, const char *command, int status)
{
    history[*count].pid = pid;
    strcpy(history[*count].command, command);
    history[*count].status = status;
    (*count)++;
}

void write_history_to_file(Process history[], int count, const char *filename)
{
    FILE *fp = fopen(filename, "w");
    if (!fp)
    {
        perror("Failed to open history file");
        return;
    }
    for (int i = 0; i < count; i++)
    {
        fprintf(fp, "%d | %s | %d\n", history[i].pid, history[i].command, history[i].status);
    }
    fclose(fp);
}
